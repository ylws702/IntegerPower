#pragma once
#include <cctype>
#include <iostream>
#include <vector>
class BigInteger
{
    using Node = std::uint8_t;
public:
    inline void Clear();
    const std::vector<Node>& GetBits() const;
    friend std::istream& operator>>(std::istream& is, BigInteger&i);
    friend std::ostream& operator<<(std::ostream& os, const BigInteger&i);
    friend std::ostream& operator<<(std::ostream& os, const BigInteger&&i);

protected:
    std::vector<Node> bits;
};

