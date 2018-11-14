#include "pch.h"
#include "BinaryBigInteger.h"


BinaryBigInteger::BinaryBigInteger(const DecimalBigInteger && decimal)
{
    //十进制数容器
    auto bits = std::move(decimal).GetBits();
    //余数
    Node remainder;
    int length, i;
    //采用循环除二求余数方法
    //将十进制转为二进制
    while (!bits.empty())
    {
        length = (int)bits.size();
        remainder = 0;
        //每位除以二
        //余数给低位
        for (i = length; --i >= 0;)
        {
            remainder = bits[i] + (remainder == 1 ? 10 : 0);
            bits[i] = remainder / 2;
            remainder %= 2;
        }
        //余数即为转为二进制的位
        this->bits.emplace_back(remainder == 0 ? 0 : 1);
        //去掉头部的0
        if (bits.back() == 0)
        {
            bits.pop_back();
        }
    }
}

DecimalBigInteger BinaryBigInteger::ToDecimalBigInteger() const
{
    //结果
    DecimalBigInteger result;
    //二进制容器大小
    int length1 = (int)this->bits.size(),
        //log10(2)=0.30102999566398120..
        //十进制容器大小
        length2 = (int)(length1*0.30102999566398120) + 1,
        //计数
        i, j;
    //二进制为0，直接返回
    if (length1 == 1 && this->bits[0] == 0)
    {
        return result;
    }
    //十进制容器
    Num bits(length2, 0),
        //二的幂
        powerOfTwo(1, 1);
    bits[0] = this->bits[0] == 0 ? 0 : 1;
    //不断计算二的幂
    //并根据二进制加到结果上
    for (i = 1; i < length1; ++i)
    {
        //计算二的幂（十进制）
        length2 = (int)powerOfTwo.size();
        for (j = 0; j < length2; ++j)
        {
            powerOfTwo[j] <<= 1;
        }
        //进位处理
        for (j = 0; j < length2 - 1; ++j)
        {
            if (powerOfTwo[j] > 9)
            {
                powerOfTwo[j] -= 10;
                ++powerOfTwo[j + 1];
            }
        }
        //最高位进位处理
        if (powerOfTwo[j] > 9)
        {
            powerOfTwo[j] -= 10;
            powerOfTwo.emplace_back(1);
            ++length2;
        }
        //如果二进制该位为1，加上二的幂
        if (this->bits[i] == 1)
        {
            //逐位相加
            for (j = 0; j < length2; ++j)
            {
                bits[j] += powerOfTwo[j];
            }
            //进位处理
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
    //去掉头部的0
    while (bits.back() == 0)
    {
        bits.pop_back();
    }
    //容器转整数
    result.SetBits(bits);
    return result;
}
