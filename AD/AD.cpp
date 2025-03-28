// AD.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ADVariable.h"
#include <iostream>


int main()
{
    // Create variables
    double value = 1.5;


    try {
        ADVariable x = make_variable(value);

        ADVariable g = (pow(x, 2.0) - 5) * (4 - 3 * x);
        ADVariable f = 5 + pow(x, 3.0) - log(g) / (x - 4);

        // function example
        std::cout << "At x = 2:\n";
        std::cout << "f(x) = " << f.value() << "\n";
        std::cout << "f'(x) = " << f.derivative() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    //test against numerical differential

    auto g_ = [](double x) {return (pow(x, 2.0) - 5) * (4 - 3 * x);};
    auto f_ = [&](double x) {return 5 + pow(x, 3.0) - log(g_(x)) / (x - 4); };

    double eps = 1e-4;

    std::cout << "f_(x) = " << f_(value) << "\n";
    std::cout << "f'_(x) = " << (f_(value + eps) - f_(value - eps)) / (2.0 * eps) << "\n";


    return 0;
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
