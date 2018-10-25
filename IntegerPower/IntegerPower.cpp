// IntegerPower.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>

class BigInteger
{
public:
    BigInteger();
    inline void Clear();
    BigInteger operator^(const BigInteger& a)const;
    BigInteger& operator*=(const BigInteger& a);
    bool operator!=(const BigInteger&a)const;
    BigInteger& operator++();
    friend std::istream&operator>>(std::istream& is, BigInteger&i);
    friend std::ostream&operator<<(std::ostream& os, const BigInteger&i);
    friend std::ostream&operator<<(std::ostream& os, const BigInteger&&i);

private:
    std::vector<uint8_t> bits;
};

BigInteger::BigInteger()
{
    this->bits.emplace_back(0);
    std::cout << "struct called\n";
}

inline void BigInteger::Clear()
{
    this->bits.clear();
}

BigInteger BigInteger::operator^(const BigInteger & a) const
{
    if (a.bits.size() == 1)
    {
        if (a.bits[0] == 0)
        {
            return BigInteger();
        }
        else if (a.bits[0] == 1)
        {
            return *this;
        }
    }
    BigInteger result = *this;
    for (BigInteger i{}; i != a; ++i)
    {
        result *= *this;
    }
    return result;
}

BigInteger & BigInteger::operator*=(const BigInteger & a)
{
    decltype(a.bits) result;
    decltype(result)::value_type tmp;
    int length1 = this->bits.size(), length2 = a.bits.size(), i, j, k;
    result.resize(length1 + length2, 0);
    for (i = 0; i < length1; ++i)
    {
        for (j = 0; j < length2; ++j)
        {
            tmp = this->bits[i] * a.bits[j];
            k = i + j;
            result[k] += tmp % 10;
            if (result[k] > 9)
            {
                result[k] -= 10;
                ++result[k + 1];
            }
            ++k;
            result[k] += tmp / 10;
            while (result[k] > 9)
            {
                result[k] -= 10;
                ++k;
                ++result[k];
            }
        }
    }
    if (result.back() == 0)
    {
        result.pop_back();
    }
    this->bits = result;
    return *this;
}

bool BigInteger::operator!=(const BigInteger & a) const
{
    int length = this->bits.size(), i;
    if (a.bits.size() != length)
    {
        return true;
    }
    for (i = 0; i < length; ++i)
    {
        if (this->bits[i] != a.bits[i])
        {
            return true;
        }
    }
    return false;
}

BigInteger & BigInteger::operator++()
{
    int i = 0;
    ++this->bits[i];
    this->bits.emplace_back(0);
    while (this->bits[i] > 9)
    {
        this->bits[i] = 0;
        ++i;
        ++this->bits[i];
    }
    if (this->bits.back() == 0)
    {
        this->bits.pop_back();
    }
    return *this;
}


std::istream & operator>>(std::istream& is, BigInteger & i)
{
    int bit;
    i.Clear();
    while (bit = is.get(), std::isspace(bit));
    is.putback(bit);
    while (bit = is.get(), std::isdigit(bit))
    {
        i.bits.emplace_back(bit - '0');
    }
    is.putback(bit);
    std::reverse(i.bits.begin(), i.bits.end());
    while (i.bits.size() > 1 && i.bits.back() == 0)
    {
        i.bits.pop_back();
    }
    return is;
}

std::ostream & operator<<(std::ostream & os, const BigInteger & i)
{
    return os << std::move(i);
}

std::ostream & operator<<(std::ostream & os, const BigInteger && i)
{
    for (auto it = i.bits.crbegin(); it != i.bits.crend(); ++it)
    {
        os << (unsigned)*it;
    }
    return os;
}

int main()
{
    BigInteger a, b, c;
    std::cin >> a >> b;
    c = a ^ b;
    std::cout << c << '\n' << (a^b) << '\n';
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
