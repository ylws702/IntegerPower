#include "pch.h"
#include "BinaryBigInteger.h"


BinaryBigInteger::BinaryBigInteger(const BigInteger && decimal)
{
    auto bits = decimal.GetBits();
    decltype(bits)::value_type remainder;
    int length, i;
    while (!bits.empty())
    {
        length = bits.size();
        remainder = 0;
        for (i = length; --i >= 0;)
        {
            remainder = bits[i] + (remainder == 1 ? 10 : 0);
            bits[i] = remainder / 2;
            remainder %= 2;
        }
        this->bits.emplace_back(remainder == 0 ? 0 : 1);
        if (bits.back() == 0)
        {
            bits.pop_back();
        }
    }
}

DecimalBigInteger BinaryBigInteger::ToDecimalBigInteger() const
{
    DecimalBigInteger result;
    int length1 = this->bits.size(),
        length2 = (int)(length1*0.30102999566398120) + 1,
        i, j, k;
    if (length1 == 1 && this->bits[0] == 0)
    {
        return result;
    }
    decltype(this->bits) bits(length2,0),
        powerOfTwo(1, 1);
    bits[0] = this->bits[0] == 0 ? 0 : 1;
    for (i = 1; i < length1; ++i)
    {
        length2 = powerOfTwo.size();
        for (j = 0; j < length2; ++j)
        {
            powerOfTwo[j] <<= 1;
        }
        for (j = 0; j < length2 - 1; ++j)
        {
            if (powerOfTwo[j] > 9)
            {
                powerOfTwo[j] -= 10;
                ++powerOfTwo[j + 1];
            }
        }
        if (powerOfTwo[j] > 9)
        {
            powerOfTwo[j] -= 10;
            powerOfTwo.emplace_back(1);
            ++length2;
        }
        if (this->bits[i]==1)
        {
            for (j = 0; j < length2; ++j)
            {
                bits[j] += powerOfTwo[j];
            }
            for (j = 0; j < length2; ++j)
            {
                if (bits[j] > 9)
                {
                    bits[j] -= 10;
                    ++bits[j + 1];
                }
            }
        }
    }
    while (bits.back() == 0)
    {
        bits.pop_back();
    }
    result.SetBits(bits);
    return result;
}
