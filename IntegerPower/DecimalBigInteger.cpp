#include "pch.h"
#include "DecimalBigInteger.h"


DecimalBigInteger::DecimalBigInteger()
{
    this->bits.emplace_back(0);
}

template<typename T>
DecimalBigInteger::DecimalBigInteger(T t)
{
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
        tmp *= tmp;
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
    while (len < lent)
    {
        len <<= 1;
    }
    len <<= 1;
    FFTNum fft1(len, { 0.0,0.0 }),
        fft2(len, { 0.0,0.0 });
    std::copy_n(this->bits.cbegin(), len1, fft1.begin());
    std::copy_n(a.bits.cbegin(), len2, fft2.begin());
    //使用快速傅里叶变换求出a、b的点值表示法
    this->FFT(fft1, false);
    this->FFT(fft2, false);
    //求出c的点值表示法 
    for (i = 0; i < len; ++i)
    {
        fft1[i] *= fft2[i];
    }
    //快速傅里叶逆变换求出c的系数表示法
    FFT(fft1, true);
    for (i = 0; i < len; ++i)
    {
        fft1[i] /= len;
    }
    this->bits.resize(len + 1);
    for (i = 0; i < len; ++i)
    {
        this->bits[i] = (int)(fft1[i].real() + 0.5);
    }
    for (i = 0; i < len; ++i)
    {
        this->bits[i + 1] += this->bits[i] / 10;
        this->bits[i] %= 10;
    }
    while (this->bits.back() == 0)
    {
        this->bits.pop_back();
    }
    return *this;
}

DecimalBigInteger & DecimalBigInteger::operator++()
{
    int i = 0;
    ++this->bits[i];
    this->bits.emplace_back(0);
    while (this->bits[i] > 9)
    {
        this->bits[i] = 0;
        ++i;
        ++this->bits[i];
    }
    if (this->bits.back() == 0)
    {
        this->bits.pop_back();
    }
    return *this;
}