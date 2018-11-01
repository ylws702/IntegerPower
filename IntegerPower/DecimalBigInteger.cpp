#include "pch.h"
#include "DecimalBigInteger.h"


DecimalBigInteger::DecimalBigInteger()
{
    this->bits.emplace_back(0);
}

template<typename T>
DecimalBigInteger::DecimalBigInteger(T t)
{
    static_assert(std::is_integral<T>::value, "Integral required.");
    this->Clear();
    while (t != 0)
    {
        this->bits.emplace_back(t % 10);
        t /= 10;
    }
}

DecimalBigInteger DecimalBigInteger::operator^(const DecimalBigInteger & a) const
{
    if (a.bits.size() == 1)
    {
        if (a.bits[0] == 0)
        {
            return 1;
        }
        else if (a.bits[0] == 1)
        {
            return *this;
        }
    }
    auto power = BinaryBigInteger(a).GetBits();
    DecimalBigInteger tmp=*this, 
        result;
    int length = power.size(), i;
    if (power[0]==1)
    {
        result = tmp;
    }
    else
    {
        result = 1;
    }
    for (i = 1; i < length; i++)
    {
        tmp *= tmp;
        if (power[i]==1)
        {
            result *= tmp;
        }
    }
    return result;
}

DecimalBigInteger & DecimalBigInteger::operator*=(const DecimalBigInteger & a)
{
    decltype(a.bits) result;
    decltype(result)::value_type tmp;
    int length1 = (int)this->bits.size(),
        length2 = (int)a.bits.size(),
        i, j, k;
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

bool DecimalBigInteger::operator!=(const DecimalBigInteger & a) const
{
    int length = (int)this->bits.size(),
        i;
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

DecimalBigInteger & DecimalBigInteger::operator++()
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