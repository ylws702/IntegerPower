#pragma once
#include "BigInteger.h"
#include "DecimalBigInteger.h"
class BinaryBigInteger :
    public BigInteger
{
public:
    BinaryBigInteger() {}
    BinaryBigInteger(const BigInteger& bigInt) :BinaryBigInteger(std::move(bigInt)) {}
    BinaryBigInteger(const BigInteger&& bigInt);
    DecimalBigInteger ToDecimalBigInteger()const;
};

