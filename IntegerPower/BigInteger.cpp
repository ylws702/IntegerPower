#include "pch.h"
#include "BigInteger.h"

inline void BigInteger::Clear()
{
    this->bits.clear();
}

const std::vector<BigInteger::Node>& BigInteger::GetBits() const
{
    return std::as_const(this->bits);
}

void BigInteger::SetBits(const std::vector<Node>& bits)
{
    this->bits = bits;
}

void BigInteger::Print() const
{
    char* str = new char[this->bits.size()+1];
    int i = -1;
    for (auto it = this->bits.cbegin(); it != this->bits.cend(); ++it)
    {
        str[++i] = *it + '0';
    }
    str[++i] = '\0';
    std::printf("%s", str);
    delete[] str;
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
    char *str = new char[i.bits.size() + 1];
    int j = -1;
    for (auto it = i.bits.crbegin(); it != i.bits.crend(); ++it)
    {
        str[++j] = *it + '0';
    }
    str[++j] = '\0';
    os << str;
    delete[] str;
    return os;
}