#pragma once
#include "BigInteger.h"
#include "DecimalBigInteger.h"
class BinaryBigInteger :
    public BigInteger
{
public:
    //Ĭ�Ϲ���
    BinaryBigInteger() {}
    //ʹ��ʮ������ֵ����
    BinaryBigInteger(const DecimalBigInteger& bigInt) :
        BinaryBigInteger(std::move(bigInt)) {}
    //ʹ��ʮ������ֵ����
    BinaryBigInteger(const DecimalBigInteger&& bigInt);
    //תʮ����,Ч�ʵ�
    virtual DecimalBigInteger ToDecimalBigInteger()const;
};

