#pragma once
#include "BigInteger.h"
class DecimalBigInteger :
    public BigInteger
{
public:
    DecimalBigInteger();
    template<typename T>
    DecimalBigInteger(T t);
    DecimalBigInteger operator^(const DecimalBigInteger & a) const;
    DecimalBigInteger& operator*=(const DecimalBigInteger& a);
    bool operator!=(const DecimalBigInteger&a)const;
    DecimalBigInteger& operator++();
};

