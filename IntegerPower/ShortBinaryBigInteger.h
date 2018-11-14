#pragma once
#include "BinaryBigInteger.h"
class ShortBinaryBigInteger :
    public BigInteger
{
    //线性表元素位长度;
    const int bitsCount = sizeof(decltype(bits)::value_type) / 2 * 8;
public:
    //默认构造函数
    ShortBinaryBigInteger() {}
    //使用整形数字构造
    template<typename T>
    ShortBinaryBigInteger(T t);
    //使用十进制左值构造
    ShortBinaryBigInteger(const DecimalBigInteger& bigInt) :
        ShortBinaryBigInteger(BinaryBigInteger(std::move(bigInt))) {}
    //使用十进制右值构造
    ShortBinaryBigInteger(const DecimalBigInteger&& bigInt) :
        ShortBinaryBigInteger(BinaryBigInteger(std::move(bigInt))) {}
    //使用二进制左值构造
    ShortBinaryBigInteger(const BinaryBigInteger& bigInt) :
        ShortBinaryBigInteger(std::move(bigInt)) {}
    //使用二进制右值构造
    ShortBinaryBigInteger(const BinaryBigInteger&& bigInt);

    //乘赋值
    ShortBinaryBigInteger& operator*=(const ShortBinaryBigInteger& a);
    //取幂
    ShortBinaryBigInteger operator^(const BinaryBigInteger & a) const;
    //赋值
    ShortBinaryBigInteger& operator=(const ShortBinaryBigInteger& a);
    //转二进制
    virtual BinaryBigInteger ToBinaryBigInteger()const;
    //删除FFT算法
    void FFT(std::vector<FFTNode>& re, std::vector<FFTNode>& in, unsigned n, bool flag)=delete;
};
