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
    auto bits = std::move(bigInt).GetBits();
    int length = (int)bits.size() / this->bitsCount,
        rest = bits.size() % this->bitsCount,
        i, j;
    this->bits = decltype(bits)(length + 1, 0);
    for (i = 0; i < length; ++i)
    {
        this->bits[i] |= bits[(i + 1)*this->bitsCount - 1];
        for (j = this->bitsCount - 1; --j >= 0; )
        {
            this->bits[i] <<= 1;
            this->bits[i] |= bits[i*this->bitsCount + j];
        }
    }
    if (rest != 0)
    {
        this->bits[i] |= bits[bits.size() - 1];
        for (j = 1; j < rest; ++j)
        {
            this->bits[i] <<= 1;
            this->bits[i] |= bits[bits.size() - 1 - j];
        }
    }
    while (this->bits.back() == 0)
    {
        this->bits.pop_back();
    }
}

ShortBinaryBigInteger & ShortBinaryBigInteger::operator*=(const ShortBinaryBigInteger & a)
{
    decltype(a.bits) result;
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
            if (result[k] < tmp)//溢出
            {
                do
                {
                    ++k;
                    ++result[k];//向前进位
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
        if (result[i] < tmp)//溢出
        {
            do
            {
                ++i;
                ++result[i];//向前进位
            } while (result[i] == 0u);//自加溢出
            --i;//处理当前高位
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
        tmp *= tmp;
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
    decltype(this->bits) bits;
    BinaryBigInteger result;
    int length = (int)this->bits.size(),
        i,j;
    Node tmp;
    bits.resize(length*this->bitsCount);
    for ( i = 0; i < length; ++i)
    {
        tmp = this->bits[i];
        bits[i*this->bitsCount] = tmp % 2;
        for ( j = 1; j < this->bitsCount; j++)
        {
            tmp >>= 1;
            bits[i*this->bitsCount+j]= tmp % 2;
        }
    }
    while (bits.back()==0)
    {
        bits.pop_back();
    }
    result.SetBits(bits);
    return result;
}

