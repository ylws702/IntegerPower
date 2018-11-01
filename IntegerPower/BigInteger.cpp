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
    for (auto it = i.bits.crbegin(); it != i.bits.crend(); ++it)
    {
        os << (unsigned)*it;
    }
    return os;
}