#pragma once
#include "BigInteger.h"
#include "DecimalBigInteger.h"
class BinaryBigInteger :
    public BigInteger
{
public:
    //默认构造
    BinaryBigInteger() {}
    //使用十进制左值构造
    BinaryBigInteger(const DecimalBigInteger& bigInt) :
        BinaryBigInteger(std::move(bigInt)) {}
    //使用十进制右值构造
    BinaryBigInteger(const DecimalBigInteger&& bigInt);
    //转十进制,效率低
    virtual DecimalBigInteger ToDecimalBigInteger()const;
};

