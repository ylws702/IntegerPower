#include "pch.h"
#include "DecimalBigInteger.h"


DecimalBigInteger::DecimalBigInteger()
{
    this->bits.emplace_back(0);
}

template<typename T>
DecimalBigInteger::DecimalBigInteger(T t)
{
    //T����Ϊ����
    static_assert(std::is_integral<T>::value, "Integral required.");
    this->Clear();
    while (t != 0)
    {
        this->bits.emplace_back(t % 10);
        t /= 10;
    }
}

DecimalBigInteger DecimalBigInteger::operator^(const DecimalBigInteger & a) const
{
    //�ȴ����ָ��0��1
    if (a.bits.size() == 1)
    {
        if (a.bits[0] == 0)
        {
            return 1;
        }
        else if (a.bits[0] == 1)
        {
            return *this;
        }
    }
    auto power = BinaryBigInteger(a).GetBits();
    DecimalBigInteger tmp = *this,
        result;
    int length = (int)power.size(), i;
    //ƽ�����㷨
    if (power[0] == 1)
    {
        result = tmp;
    }
    else
    {
        result = 1;
    }
    for (i = 1; i < length; ++i)
    {
        //����ƽ��
        tmp *= tmp;
        //ָ�������Ƶ�iλΪ1�ͳ���tmp
        if (power[i] == 1)
        {
            result *= tmp;
        }
    }
    return result;
}

DecimalBigInteger& DecimalBigInteger::operator*=(const DecimalBigInteger & a)
{
    int len1 = (int)this->bits.size(),
        len2 = (int)a.bits.size(),
        lent = std::max(len1, len2),
        len = 1,
        i;
    //����������СΪ2^k��ʽ������FFT�㷨
    while (len < lent)
    {
        len <<= 1;
    }
    len <<= 1;
    //��������
    FFTNum fft1(len, { 0.0,0.0 }),
        fft2(len, { 0.0,0.0 });
    //����������������
    std::copy_n(this->bits.cbegin(), len1, fft1.begin());
    std::copy_n(a.bits.cbegin(), len2, fft2.begin());
    //ʹ�ÿ��ٸ���Ҷ�任���a��b�ĵ�ֵ��ʾ��
    this->FFT(fft1, false);
    this->FFT(fft2, false);
    //���c�ĵ�ֵ��ʾ�� 
    for (i = 0; i < len; ++i)
    {
        fft1[i] *= fft2[i];
    }
    //���ٸ���Ҷ��任���c��ϵ����ʾ��
    FFT(fft1, true);
    for (i = 0; i < len; ++i)
    {
        fft1[i] /= len;
    }
    this->bits.resize(len + 1);
    //��������������ת������
    for (i = 0; i < len; ++i)
    {
        this->bits[i] = (int)(fft1[i].real() + 0.5);
    }
    //ÿλ������������λ
    for (i = 0; i < len; ++i)
    {
        this->bits[i + 1] += this->bits[i] / 10;
        this->bits[i] %= 10;
    }
    //ȥ��ͷ����0
    while (this->bits.back() == 0)
    {
        this->bits.pop_back();
    }
    return *this;
}

DecimalBigInteger & DecimalBigInteger::operator++()
{
    int i = 0;
    //���λ�Լ�
    ++this->bits[i];
    //��Ԫ�ط�ֹ99999���Լӵ�������Խ��
    this->bits.emplace_back(0);
    //��9ѭ����ǰ��λ
    while (this->bits[i] > 9)
    {
        this->bits[i] = 0;
        ++i;
        ++this->bits[i];
    }
    //ȥ��ͷ����0
    if (this->bits.back() == 0)
    {
        this->bits.pop_back();
    }
    return *this;
}

void DecimalBigInteger::PrintN(int n)
{
    //ָ��-1
    int e = this->bits.size(),
        i = -1;
    if (e == 0 || n <= 0)
    {
        return;
    }
    //Ҫ�����Чλ��̫��
    if (n >= e)
    {
        std::cout << this->bits.back() << '.';
        auto str = std::make_unique<char[]>(e);
        for (auto it = this->bits.crbegin() + 1;
            it != this->bits.crend();
            ++it)
        {
            str[++i] = *it + '0';
        }
        str[++i] = '\0';
        std::cout << str;
        for (++i; i < n; ++i)
        {
            std::cout << '0';
        }
        std::cout << "e+" << e - 1;
        return;
    }
    //�����Լӷ���ʵ�����������Ľ�λ
    DecimalBigInteger p;
    p.bits = Num(this->bits.cend() - n, this->bits.cend());
    int size = p.bits.size();
    //��������
    if (auto t = *(this->bits.cend() - n - 1);
        t >= 5)
    {
        ++p;
        if (size != p.bits.size())
        {
            //9.x��λΪ1.000��
            std::cout << "1.";
            for (i = 1; i < n; ++i)
            {
                std::cout << '0';
            }
            std::cout << "e+" << e;
            return;
        }
    }
    std::cout << p.bits.back() << '.';
    auto str = std::make_unique<char[]>(n);
    for (auto it = p.bits.crbegin() + 1;
        it != p.bits.crend();
        ++it)
    {
        str[++i] = *it + '0';
    }
    str[++i] = '\0';
    std::cout << str;
    std::cout << "e+" << e - 1;
}
