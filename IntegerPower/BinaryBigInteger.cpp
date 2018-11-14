#include "pch.h"
#include "BinaryBigInteger.h"


BinaryBigInteger::BinaryBigInteger(const DecimalBigInteger && decimal)
{
    //ʮ����������
    auto bits = std::move(decimal).GetBits();
    //����
    Node remainder;
    int length, i;
    //����ѭ����������������
    //��ʮ����תΪ������
    while (!bits.empty())
    {
        length = (int)bits.size();
        remainder = 0;
        //ÿλ���Զ�
        //��������λ
        for (i = length; --i >= 0;)
        {
            remainder = bits[i] + (remainder == 1 ? 10 : 0);
            bits[i] = remainder / 2;
            remainder %= 2;
        }
        //������ΪתΪ�����Ƶ�λ
        this->bits.emplace_back(remainder == 0 ? 0 : 1);
        //ȥ��ͷ����0
        if (bits.back() == 0)
        {
            bits.pop_back();
        }
    }
}

DecimalBigInteger BinaryBigInteger::ToDecimalBigInteger() const
{
    //���
    DecimalBigInteger result;
    //������������С
    int length1 = (int)this->bits.size(),
        //log10(2)=0.30102999566398120..
        //ʮ����������С
        length2 = (int)(length1*0.30102999566398120) + 1,
        //����
        i, j;
    //������Ϊ0��ֱ�ӷ���
    if (length1 == 1 && this->bits[0] == 0)
    {
        return result;
    }
    //ʮ��������
    Num bits(length2, 0),
        //������
        powerOfTwo(1, 1);
    bits[0] = this->bits[0] == 0 ? 0 : 1;
    //���ϼ��������
    //�����ݶ����Ƽӵ������
    for (i = 1; i < length1; ++i)
    {
        //��������ݣ�ʮ���ƣ�
        length2 = (int)powerOfTwo.size();
        for (j = 0; j < length2; ++j)
        {
            powerOfTwo[j] <<= 1;
        }
        //��λ����
        for (j = 0; j < length2 - 1; ++j)
        {
            if (powerOfTwo[j] > 9)
            {
                powerOfTwo[j] -= 10;
                ++powerOfTwo[j + 1];
            }
        }
        //���λ��λ����
        if (powerOfTwo[j] > 9)
        {
            powerOfTwo[j] -= 10;
            powerOfTwo.emplace_back(1);
            ++length2;
        }
        //��������Ƹ�λΪ1�����϶�����
        if (this->bits[i] == 1)
        {
            //��λ���
            for (j = 0; j < length2; ++j)
            {
                bits[j] += powerOfTwo[j];
            }
            //��λ����
            for (j = 0; j < length2; ++j)
            {
                if (bits[j] > 9)
                {
                    bits[j] -= 10;
                    ++bits[j + 1];
                }
            }
        }
    }
    //ȥ��ͷ����0
    while (bits.back() == 0)
    {
        bits.pop_back();
    }
    //����ת����
    result.SetBits(bits);
    return result;
}
