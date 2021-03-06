// IntegerPower.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <chrono>
#include <iostream>
#include "DecimalBigInteger.h"
#include "BinaryBigInteger.h"
#include "ShortBinaryBigInteger.h"

int main()
{
    //时钟
    using Clock = std::chrono::high_resolution_clock;
    //时间间隔
    using Duration = std::chrono::duration<double>;
    //大整数
    DecimalBigInteger a, b, c;
    std::cout << "底数: ";
    std::cin >> a;
    std::cout << "指数: ";
    std::cin >> b;
    //获取时间t0
    auto t0 = Clock::now();
    //取幂
    c = a ^ b;
    //打印十进制幂
    std::cout << "十进制: " << c << '\n';
    //获取时间t1
    auto t1 = Clock::now();
    //二进制幂
    ShortBinaryBigInteger g;
    //使用二进制计算
    g = ShortBinaryBigInteger(a) ^ BinaryBigInteger(b);
    //打印二进制幂
    std::cout << "二进制: " << g.ToBinaryBigInteger() << '\n';
    //获取时间t2
    auto t2 = Clock::now();
    //打印结果十位有效数字
    std::cout << "结果: ";
    c.PrintN(10);
    std::cout << '\n';
    //打印时间t1-t0
    std::cout << "十进制计算时间: "
        << Duration(t1 - t0).count()
        << "(s)\n";
    //打印时间t2-t1
    std::cout << "二进制计算时间: "
        << Duration(t2 - t1).count()
        << "(s)\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
