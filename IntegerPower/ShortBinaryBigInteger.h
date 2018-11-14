#pragma once
#include "BinaryBigInteger.h"
class ShortBinaryBigInteger :
    public BigInteger
{
    //���Ա�Ԫ��λ����;
    const int bitsCount = sizeof(decltype(bits)::value_type) / 2 * 8;
public:
    //Ĭ�Ϲ��캯��
    ShortBinaryBigInteger() {}
    //ʹ���������ֹ���
    template<typename T>
    ShortBinaryBigInteger(T t);
    //ʹ��ʮ������ֵ����
    ShortBinaryBigInteger(const DecimalBigInteger& bigInt) :
        ShortBinaryBigInteger(BinaryBigInteger(std::move(bigInt))) {}
    //ʹ��ʮ������ֵ����
    ShortBinaryBigInteger(const DecimalBigInteger&& bigInt) :
        ShortBinaryBigInteger(BinaryBigInteger(std::move(bigInt))) {}
    //ʹ�ö�������ֵ����
    ShortBinaryBigInteger(const BinaryBigInteger& bigInt) :
        ShortBinaryBigInteger(std::move(bigInt)) {}
    //ʹ�ö�������ֵ����
    ShortBinaryBigInteger(const BinaryBigInteger&& bigInt);

    //�˸�ֵ
    ShortBinaryBigInteger& operator*=(const ShortBinaryBigInteger& a);
    //ȡ��
    ShortBinaryBigInteger operator^(const BinaryBigInteger & a) const;
    //��ֵ
    ShortBinaryBigInteger& operator=(const ShortBinaryBigInteger& a);
    //ת������
    virtual BinaryBigInteger ToBinaryBigInteger()const;
    //ɾ��FFT�㷨
    void FFT(std::vector<FFTNode>& re, std::vector<FFTNode>& in, unsigned n, bool flag)=delete;
};
