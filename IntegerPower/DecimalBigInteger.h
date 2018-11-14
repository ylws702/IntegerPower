#pragma once

#include "BigInteger.h"
#include "BinaryBigInteger.h"
class DecimalBigInteger :
    public BigInteger
{
public:
    //默认构造
    DecimalBigInteger();
    //整数类型构造
    template<typename T>
    DecimalBigInteger(T t);
    //取幂
    DecimalBigInteger operator^(const DecimalBigInteger & a) const;
    //乘赋值
    DecimalBigInteger& operator*=(const DecimalBigInteger& a);
    //自加
    DecimalBigInteger& operator++();
};

