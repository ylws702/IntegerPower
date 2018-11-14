#include "pch.h"
#include "ShortBinaryBigInteger.h"

template<typename T>
inline ShortBinaryBigInteger::ShortBinaryBigInteger(T t)
{
    static_assert(std::is_integral<T>::value, "Integral required.");
    this->Clear();
    const Node mod = Node(1) << this->bitsCount;
    while (t != T(0))
    {
        this->bits.emplace_back(t % mod);
        t /= mod;
    }
}

ShortBinaryBigInteger::ShortBinaryBigInteger(const BinaryBigInteger && bigInt)
{
    //紧缩处理前容器
    auto bits = std::move(bigInt).GetBits();
    //紧缩处理后容器大小
    int length = (int)bits.size() / this->bitsCount,
        //多出的二进制位数，高位补零
        rest = bits.size() % this->bitsCount,
        i, j;
    //紧缩处理后容器
    this->bits = Num(length + 1, 0);
    //对能整除部分二进制位进行紧缩处理
    for (i = 0; i < length; ++i)
    {
        this->bits[i] |= bits[(i + 1)*this->bitsCount - 1];
        for (j = this->bitsCount - 1; --j >= 0; )
        {
            this->bits[i] <<= 1;
            this->bits[i] |= bits[i*this->bitsCount + j];
        }
    }
    //对多出的二进制位进行紧缩处理
    if (rest != 0)
    {
        this->bits[i] |= bits[bits.size() - 1];
        for (j = 1; j < rest; ++j)
        {
            this->bits[i] <<= 1;
            this->bits[i] |= bits[bits.size() - 1 - j];
        }
    }
    //去掉高位的0
    while (this->bits.back() == 0)
    {
        this->bits.pop_back();
    }
}

ShortBinaryBigInteger & ShortBinaryBigInteger::operator*=(const ShortBinaryBigInteger & a)
{
    Num result;
    Node tmp;
    const Node lowerBits = (1 << bitsCount) - 1;
    int length1 = (int)this->bits.size(),
        length2 = (int)a.bits.size(),
        i, j, k;
    result.resize(length1 + length2, 0u);
    for (i = 0; i < length1; ++i)
    {
        for (j = 0; j < length2; ++j)
        {
            tmp = this->bits[i] * a.bits[j];
            k = i + j;
            result[k] += tmp;
            //溢出处理
            if (result[k] < tmp)
            {
                do
                {
                    ++k;
                    //向前进位
                    ++result[k];
                } while (result[k] == 0u);//自加溢出
            }
        }
    }
    for (i = 0; i < length1 + length2 - 1;)
    {
        tmp = result[i] >> (this->bitsCount);
        if (tmp == 0u)
        {
            ++i;
            continue;
        }
        result[i] &= lowerBits;
        ++i;
        result[i] += tmp;
        //溢出处理
        if (result[i] < tmp)
        {
            do
            {
                ++i;
                //向前进位
                ++result[i];
            } while (result[i] == 0u);//自加溢出
            //处理当前高位
            --i;
        }
    }
    if (result.back() == 0u)
    {
        result.pop_back();
    }
    this->bits = result;
    return *this;
}

ShortBinaryBigInteger ShortBinaryBigInteger::operator^(const BinaryBigInteger & a) const
{
    //先处理简单指数0和1
    auto power = a.GetBits();
    if (power.size() == 1)
    {
        if (power[0] == 0)
        {
            return 1;
        }
        else if (power[0] == 1)
        {
            return *this;
        }
    }
    ShortBinaryBigInteger tmp = *this,
        result;
    int length = (int)power.size(), i;
    //平方幂算法
    if (power[0] == 1)
    {
        result.SetBits(tmp.GetBits());
    }
    else
    {
        result.SetBits(ShortBinaryBigInteger(1).GetBits());
    }
    for (i = 1; i < length; i++)
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

ShortBinaryBigInteger & ShortBinaryBigInteger::operator=(const ShortBinaryBigInteger & a)
{
    this->bits = a.bits;
    return *this;
}

BinaryBigInteger ShortBinaryBigInteger::ToBinaryBigInteger() const
{
    Num bits;
    BinaryBigInteger result;
    //展开处理后长度
    int length = (int)this->bits.size(),
        //计数
        i, j;
    Node tmp;
    bits.resize(length*this->bitsCount);
    //二进制位展开处理
    for (i = 0; i < length; ++i)
    {
        tmp = this->bits[i];
        bits[i*this->bitsCount] = tmp % 2;
        for (j = 1; j < this->bitsCount; j++)
        {
            tmp >>= 1;
            bits[i*this->bitsCount + j] = tmp % 2;
        }
    }
    while (bits.back() == 0)
    {
        bits.pop_back();
    }
    result.SetBits(bits);
    return result;
}

