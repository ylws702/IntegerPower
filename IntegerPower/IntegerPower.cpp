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
    DecimalBigInteger a, b,c;
    ShortBinaryBigInteger ddd;
    std::cout << "底数: ";
    std::cin >> a;
    std::cout << "指数: ";
    std::cin >> b;
#if DEBUG
    c = a ^ b;
    std::chrono::high_resolution_clock clock;
    auto t0 = clock.now();
    c.Print();
    putchar('\n');
    auto t1 = clock.now();
    std::cout << c << '\n';
    auto t2 = clock.now();
    std::cout << (t1 - t0).count() << ' ' << (t2 - t1).count();
#else
    ShortBinaryBigInteger g;
    g=ShortBinaryBigInteger(a)^ BinaryBigInteger(b);
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
