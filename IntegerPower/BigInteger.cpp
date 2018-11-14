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
    //ֱ�Ӵ�ӡ�ַ�����ѭ����ӡ�ַ�����
    //����bits.size() + 1��С��char������
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
    int i, k, j, //����
        m = 1, n = (int)a.size(),
        t, //����������ʱ����
        log2n = (int)std::log2(n);
    //ʹ�÷ǵݹ�ķ���,���Ƚ�����������
    for (i = 0; i < n; ++i)
    {
        //��תi�Ķ�����λ
        for (k = 0, j = 0, t = i;
            k < log2n;
            ++k)
        {
            j <<= 1;
            j |= t & 1;
            t >>= 1;
        }
        //����Ԫ��
        if (j > i)
        {
            std::swap(a[i], a[j]);
        }
    }
    for (i = 1; i <= log2n; ++i)
    {
        //x^m==1�ĸ�����
        FFTNode wm(cos(pi / m), flag ? -sin(pi / m) : sin(pi / m));
        for (j = 0; j < n; j += 2 * m)
        {
            //wm��1,2,4,...,2^m�η�
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
    //ȥ��ͷ����space
    while (bit = is.get(), std::isspace(bit));
    is.putback(bit);
    while (bit = is.get(), std::isdigit(bit))
    {
        i.bits.emplace_back(bit - '0');
    }
    //�Żص�һ����������
    is.putback(bit);
    //����洢
    std::reverse(i.bits.begin(), i.bits.end());
    //ȥ����λ����
    while (i.bits.size() > 1 && i.bits.back() == 0)
    {
        i.bits.pop_back();
    }
    return is;
}

std::ostream & operator<<(std::ostream & os, const BigInteger & i)
{
    //ʹ��ת�����
    return os << std::move(i);
}

std::ostream & operator<<(std::ostream & os, const BigInteger && i)
{
    //ֱ�Ӵ�ӡ�ַ�����ѭ����ӡ�ַ�����
    //����bits.size() + 1��С��char������
    auto str = std::make_unique<char[]>(std::move(i).bits.size() + 1);
    int j = -1;
    //���μ���'0'
    for (auto it = std::move(i).bits.crbegin();
        it != std::move(i).bits.crend();
        ++it)
    {
        str[++j] = *it + '0';
    }
    //����β����'\0'
    str[++j] = '\0';
    //��ӡ���
    os << str;
    return os;
}