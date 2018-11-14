#include "pch.h"
#include "DecimalBigInteger.h"


DecimalBigInteger::DecimalBigInteger()
{
    this->bits.emplace_back(0);
}

template<typename T>
DecimalBigInteger::DecimalBigInteger(T t)
{
    //T必须为整形
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
    //先处理简单指数0和1
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
    //平方幂算法
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
        //不断平方
        tmp *= tmp;
        //指数二进制第i位为1就乘上tmp
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
    //浮点容器大小为2^k形式以满足FFT算法
    while (len < lent)
    {
        len <<= 1;
    }
    len <<= 1;
    //浮点容器
    FFTNum fft1(len, { 0.0,0.0 }),
        fft2(len, { 0.0,0.0 });
    //复制整数到浮点数
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
    //浮点数四舍五入转定点数
    for (i = 0; i < len; ++i)
    {
        this->bits[i] = (int)(fft1[i].real() + 0.5);
    }
    //每位数据溢出给向高位
    for (i = 0; i < len; ++i)
    {
        this->bits[i + 1] += this->bits[i] / 10;
        this->bits[i] %= 10;
    }
    //去掉头部的0
    while (this->bits.back() == 0)
    {
        this->bits.pop_back();
    }
    return *this;
}

DecimalBigInteger & DecimalBigInteger::operator++()
{
    int i = 0;
    //最低位自加
    ++this->bits[i];
    //添元素防止99999…自加导致容器越界
    this->bits.emplace_back(0);
    //遇9循环向前进位
    while (this->bits[i] > 9)
    {
        this->bits[i] = 0;
        ++i;
        ++this->bits[i];
    }
    //去掉头部的0
    if (this->bits.back() == 0)
    {
        this->bits.pop_back();
    }
    return *this;
}

void DecimalBigInteger::PrintN(int n)
{
    //指数-1
    int e = this->bits.size(),
        i = -1;
    if (e == 0 || n <= 0)
    {
        return;
    }
    //要求的有效位数太长
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
    //借用自加方法实现四舍五入后的进位
    DecimalBigInteger p;
    p.bits = Num(this->bits.cend() - n, this->bits.cend());
    int size = p.bits.size();
    //四舍五入
    if (auto t = *(this->bits.cend() - n - 1);
        t >= 5)
    {
        ++p;
        if (size != p.bits.size())
        {
            //9.x进位为1.000…
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
