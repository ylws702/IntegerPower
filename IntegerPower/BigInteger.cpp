#include "pch.h"
#include "BigInteger.h"

inline void BigInteger::Clear()
{
    this->bits.clear();
}

const BigInteger::Num& BigInteger::GetBits() const
{
    return std::as_const(this->bits);
}

void BigInteger::SetBits(const Num& bits)
{
    this->bits = bits;
}

void BigInteger::Print() const
{
    //直接打印字符串比循环打印字符更快
    //申请bits.size() + 1大小的char型数组
    auto str = std::make_unique<char[]>(this->bits.size() + 1);
    int i = -1;
    for (auto it = this->bits.crbegin();
        it != this->bits.crend();
        ++it)
    {
        str[++i] = *it + '0';
    }
    str[++i] = '\0';
    std::printf("%s", str.get());
}

void BigInteger::FFT(FFTNum& a, bool flag)
{
    constexpr double pi = 3.1415926535897932;
    int i, k, j, //计数
        m = 1, n = (int)a.size(),
        t, //数组重排临时变量
        log2n = (int)std::log2(n);
    //使用非递归的方法,须先进行数组重排
    for (i = 0; i < n; ++i)
    {
        //反转i的二进制位
        for (k = 0, j = 0, t = i;
            k < log2n;
            ++k)
        {
            j <<= 1;
            j |= t & 1;
            t >>= 1;
        }
        //交换元素
        if (j > i)
        {
            std::swap(a[i], a[j]);
        }
    }
    for (i = 1; i <= log2n; ++i)
    {
        //x^m==1的复数根
        FFTNode wm(cos(pi / m), flag ? -sin(pi / m) : sin(pi / m));
        for (j = 0; j < n; j += 2 * m)
        {
            //wm的1,2,4,...,2^m次方
            FFTNode w(1.0, 0.0);
            for (k = 0; k < m; ++k)
            {
                FFTNode  u = a[j + k], t = a[j + k + m] * w;
                a[j + k] += t;
                a[j + k + m] = u - t;
                w *= wm;
            }
        }
        m <<= 1;
    }
}

std::istream & operator>>(std::istream& is, BigInteger & i)
{
    int bit;
    i.Clear();
    //去掉头部的space
    while (bit = is.get(), std::isspace(bit));
    is.putback(bit);
    while (bit = is.get(), std::isdigit(bit))
    {
        i.bits.emplace_back(bit - '0');
    }
    //放回第一个不是数的
    is.putback(bit);
    //反向存储
    std::reverse(i.bits.begin(), i.bits.end());
    //去掉高位的零
    while (i.bits.size() > 1 && i.bits.back() == 0)
    {
        i.bits.pop_back();
    }
    return is;
}

std::ostream & operator<<(std::ostream & os, const BigInteger & i)
{
    //使用转移输出
    return os << std::move(i);
}

std::ostream & operator<<(std::ostream & os, const BigInteger && i)
{
    //直接打印字符串比循环打印字符更快
    //申请bits.size() + 1大小的char型数组
    auto str = std::make_unique<char[]>(std::move(i).bits.size() + 1);
    int j = -1;
    //依次加上'0'
    for (auto it = std::move(i).bits.crbegin();
        it != std::move(i).bits.crend();
        ++it)
    {
        str[++j] = *it + '0';
    }
    //加上尾部的'\0'
    str[++j] = '\0';
    //打印输出
    os << str;
    return os;
}