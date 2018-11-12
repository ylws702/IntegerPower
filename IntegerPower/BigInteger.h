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
    using Node = std::uint32_t;
    using FFTNode = double;
    using FFTNum = std::vector<FFTNode>;
    static_assert(std::is_integral<Node>::value, "Integral required.");
    std::vector<Node> bits;
public:
    inline void Clear();
    const std::vector<Node>& GetBits() const;
    void SetBits(const std::vector<Node>& bits);
    friend std::istream& operator>>(std::istream& is, BigInteger&i);
    friend std::ostream& operator<<(std::ostream& os, const BigInteger&i);
    friend std::ostream& operator<<(std::ostream& os, const BigInteger&&i);
    virtual void Print()const;
    void FFT(FFTNum& re, FFTNum& in, unsigned n, bool flag);
};
