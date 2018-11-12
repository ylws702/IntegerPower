#pragma once
#include "BinaryBigInteger.h"
class ShortBinaryBigInteger :
    public BigInteger
{
    const int bitsCount = sizeof(decltype(bits)::value_type) / 2 * 8;
public:
    ShortBinaryBigInteger() {}
    template<typename T>
    ShortBinaryBigInteger(T t);
    ShortBinaryBigInteger(const DecimalBigInteger& bigInt) :
        ShortBinaryBigInteger(BinaryBigInteger(bigInt)) {}
    ShortBinaryBigInteger(const DecimalBigInteger&& bigInt) :
        ShortBinaryBigInteger(BinaryBigInteger(bigInt)) {}
    ShortBinaryBigInteger(const BinaryBigInteger& bigInt) :
        ShortBinaryBigInteger(std::move(bigInt)) {}
    ShortBinaryBigInteger(const BinaryBigInteger&& bigInt);


    ShortBinaryBigInteger& operator*=(const ShortBinaryBigInteger& a);
    ShortBinaryBigInteger operator^(const BinaryBigInteger & a) const;
    ShortBinaryBigInteger& operator=(const ShortBinaryBigInteger& a);
    virtual BinaryBigInteger ToBinaryBigInteger()const;
    void FFT(std::vector<FFTNode>& re, std::vector<FFTNode>& in, unsigned n, bool flag)=delete;
};
