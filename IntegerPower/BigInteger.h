#pragma once

#include <algorithm>
#include <cctype>
#include <complex>
#include <iostream>
#include <iterator>
#include <vector>
class BigInteger
{
protected:
    //������ʹ�����Ա�Ԫ������
    using Node = std::uint16_t;
    //������ʹ�����Ա�Ԫ�ر���Ϊ��������
    static_assert(std::is_integral<Node>::value, "Integral required.");
    //������ʹ�����Ա�����
    using Num = std::vector<Node>;
    //���ٸ���Ҷ�任ʹ�����Ա�Ԫ������
    using FFTNode = std::complex<double>;
    //���ٸ���Ҷ�任ʹ�����Ա�Ԫ�ر���Ϊ��������
    static_assert(std::is_floating_point<FFTNode::value_type>::value,
        "Floating point required.");
    //���ٸ���Ҷ�任ʹ�����Ա�����
    using FFTNum = std::vector<FFTNode>;
    //������ʹ�����Ա�
    Num bits;
public:
    //������Ա�
    inline void Clear();
    //��ȡ���������ÿһλ���ֵ����Ա�
    const Num& GetBits() const;
    //���ô��������ÿһλ���ֵ����Ա�
    void SetBits(const Num& bits);
    //ʹ��std::istream����
    friend std::istream& operator>>(std::istream& is, BigInteger&i);
    //ʹ��std::ostream��ӡ���
    friend std::ostream& operator<<(std::ostream& os, const BigInteger&i);
    //ʹ��std::ostream��ӡ���
    friend std::ostream& operator<<(std::ostream& os, const BigInteger&&i);
    //ʹ��printf��ӡ���
    virtual void Print()const;
    //���п��ٸ���Ҷ�任,reverseΪtrueʱ������任
    void FFT(FFTNum& a, bool reverse);
};
