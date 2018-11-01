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
    DecimalBigInteger result,powerOfTwo;
    
    return result;
}
