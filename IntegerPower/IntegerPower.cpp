// IntegerPower.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "DecimalBigInteger.h"
#include "BinaryBigInteger.h"
#include "ShortBinaryBigInteger.h"
#define DEBUG 1
#if DEBUG
#include <chrono>
#endif // DEBUG

int main()
{
    DecimalBigInteger a, b, c;
    std::cout << "底数: ";
    std::cin >> a;
    std::cout << "指数: ";
    std::cin >> b;
#if DEBUG
    auto t0 = std::chrono::high_resolution_clock::now();
    c = a ^ b;
    std::cout << c << '\n';
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration<double>(t1 - t0).count() << "(s)\n";
#else
    ShortBinaryBigInteger g;
    g = ShortBinaryBigInteger(a) ^ BinaryBigInteger(b);
    std::cout << g.ToBinaryBigInteger() << '\n';
#endif
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
