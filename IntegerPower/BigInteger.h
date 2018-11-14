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
    //大整数使用线性表元素类型
    using Node = std::uint16_t;
    //大整数使用线性表元素必须为整数类型
    static_assert(std::is_integral<Node>::value, "Integral required.");
    //大整数使用线性表类型
    using Num = std::vector<Node>;
    //快速傅里叶变换使用线性表元素类型
    using FFTNode = std::complex<double>;
    //快速傅里叶变换使用线性表元素必须为浮点类型
    static_assert(std::is_floating_point<FFTNode::value_type>::value,
        "Floating point required.");
    //快速傅里叶变换使用线性表类型
    using FFTNum = std::vector<FFTNode>;
    //大整数使用线性表
    Num bits;
public:
    //清空线性表
    inline void Clear();
    //获取储存大整数每一位数字的线性表
    const Num& GetBits() const;
    //设置储存大整数每一位数字的线性表
    void SetBits(const Num& bits);
    //使用std::istream输入
    friend std::istream& operator>>(std::istream& is, BigInteger&i);
    //使用std::ostream打印输出
    friend std::ostream& operator<<(std::ostream& os, const BigInteger&i);
    //使用std::ostream打印输出
    friend std::ostream& operator<<(std::ostream& os, const BigInteger&&i);
    //使用printf打印输出
    virtual void Print()const;
    //进行快速傅里叶变换,reverse为true时进行逆变换
    void FFT(FFTNum& a, bool reverse);
};
