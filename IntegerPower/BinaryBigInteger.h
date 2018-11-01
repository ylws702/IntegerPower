#pragma once
#include "BigInteger.h"
#include "DecimalBigInteger.h"
class BinaryBigInteger :
    public BigInteger
{
public:
    BinaryBigInteger() {}
    BinaryBigInteger(const DecimalBigInteger& bigInt) :
        BinaryBigInteger(std::move(bigInt)) {}
    BinaryBigInteger(const DecimalBigInteger&& bigInt);
    DecimalBigInteger ToDecimalBigInteger()const;
};

