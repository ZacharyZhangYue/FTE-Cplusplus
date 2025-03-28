// AD.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ADVariable.h"
#include <iostream>
#include <vector>

// template test functions
template<typename T>
T g(const T& x) {
    return (pow(x, 2.0) - 5) * (4 - 3 * x);
}

template<typename T>
T f(const T& x) {
    return 5 + pow(x, 3.0) - log(g(x)) / (x - 4);
}


int main()
{
    // Create values for testing
    std::vector<double> values = {-4.0, -3.0, 1.5, 1.6, 2.0, 3.0 };

    for (auto& value : values) {
        
        // auto-diff part
        try {
            ADVariable x = make_variable(value);
            std::cout << f<ADVariable>(x) << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }

        // finite-diff for testing
        double eps = 1e-4;

        std::cout << "finitediff: " << "value: " << f<double>(value)
            << " (deriv: " << (f<double>(value + eps) - f<double>(value - eps)) / (2.0 * eps) << ")" << "\n";

        std::cout << "\n";
    }

    

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
