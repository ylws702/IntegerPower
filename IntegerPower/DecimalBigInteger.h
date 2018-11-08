#pragma once

#include "BigInteger.h"
#include "BinaryBigInteger.h"
class DecimalBigInteger :
    public BigInteger
{
public:
    DecimalBigInteger();
    template<typename T>
    DecimalBigInteger(T t);
    DecimalBigInteger operator^(const DecimalBigInteger & a) const;
    DecimalBigInteger& operator*=(const DecimalBigInteger& a);
    DecimalBigInteger& operator++();
};

