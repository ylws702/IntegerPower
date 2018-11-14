#pragma once

#include "BigInteger.h"
#include "BinaryBigInteger.h"
//ʮ���ƴ�����
class DecimalBigInteger :
    public BigInteger
{
public:
    //Ĭ�Ϲ���
    DecimalBigInteger();
    //�������͹���
    template<typename T>
    DecimalBigInteger(T t);
    //ȡ��
    DecimalBigInteger operator^(const DecimalBigInteger & a) const;
    //�˸�ֵ
    DecimalBigInteger& operator*=(const DecimalBigInteger& a);
    //�Լ�
    DecimalBigInteger& operator++();
    //��ӡ�����Ŀ�ѧ��������ʽ,����nλ��Ч����
    void PrintN(int n);
};

