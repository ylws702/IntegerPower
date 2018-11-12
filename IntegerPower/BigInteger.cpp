#include "pch.h"
#include "BigInteger.h"

inline void BigInteger::Clear()
{
    this->bits.clear();
}

const std::vector<BigInteger::Node>& BigInteger::GetBits() const
{
    return std::as_const(this->bits);
}

void BigInteger::SetBits(const std::vector<Node>& bits)
{
    this->bits = bits;
}

void BigInteger::Print() const
{
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
void BigInteger::FFT(FFTNum& a, FFTNum& y, unsigned n, bool flag)
{
    constexpr double pi = 3.1415926535897932;
    int i, j, k, m = 1, t; int log2n = std::log2(n);
    for (i = 0; i < n; ++i)//Êý×éÖØÅÅ
    {
        for (j = 0, k = 0, t = i; j < log2n; ++j)
        {
            k <<= 1;
            k |= t & 1;
            t >>= 1;
        }
        if (k > i)
        {
            std::swap(a[i], a[k]);
            std::swap(y[i], y[k]);
        }
    }
    for (i = 1; i <= log2n; ++i)
    {
        double reWm = cos(pi / m), imWm = sin(pi / m);
        if (flag)
        {
            imWm = -imWm;
        }
        for (k = 0; k < n; k += 2 * m)
        {
            double reW = 1.0, imW = 0.0;
            for (j = 0; j < m; ++j)
            {
                int tag = k + j + m;
                double reT = reW * a[tag] - imW * y[tag];
                double imT = reW * y[tag] + imW * a[tag];
                double reU = a[k + j], imU = y[k + j];
                a[k + j] = reU + reT;
                y[k + j] = imU + imT;
                a[tag] = reU - reT;
                y[tag] = imU - imT;
                double reWt = reW * reWm - imW * imWm;
                double inWt = reW * imWm + imW * reWm;
                reW = reWt;
                imW = inWt;
            }
        }
        m <<= 1;
    }
}

std::istream & operator>>(std::istream& is, BigInteger & i)
{
    int bit;
    i.Clear();
    while (bit = is.get(), std::isspace(bit));
    is.putback(bit);
    while (bit = is.get(), std::isdigit(bit))
    {
        i.bits.emplace_back(bit - '0');
    }
    is.putback(bit);
    std::reverse(i.bits.begin(), i.bits.end());
    while (i.bits.size() > 1 && i.bits.back() == 0)
    {
        i.bits.pop_back();
    }
    return is;
}

std::ostream & operator<<(std::ostream & os, const BigInteger & i)
{
    return os << std::move(i);
}

std::ostream & operator<<(std::ostream & os, const BigInteger && i)
{
    auto str = std::make_unique<char[]>(std::move(i).bits.size() + 1);
    int j = -1;
    for (auto it = std::move(i).bits.crbegin();
        it != std::move(i).bits.crend(); 
        ++it)
    {
        str[++j] = *it + '0';
    }
    str[++j] = '\0';
    os << str;
    return os;
}