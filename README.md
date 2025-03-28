# Simple Automatic Differentiation

## Description

The project contains an implementation of Automatic Differentiation for univariate functions $f(x) : \mathbb{R} \to \mathbb{R}$


## Implementation

The AD process is implemented by using one single class 
```
ADVariable(value, derivative)
```

Operator overloading was implemented so that the class is compatible with its own type and built-in numerical types:
```
ADVariable x(1.0, 1.0);
ADVariable y(2.0, 2.0);

x + 1      // = 1
x / 2.0    // = 0.5
x * 3.0    // = 0.0

ADVariable z = x + y // ADVariable(3.0, 3.0)
```

At each operation, the value and derivatives will be calculated and applied to the resulting variable.

## Getting Started

### Compiling

This program is built and compiled with VisualStudio, but should be compatible with other compilers.


<img src="https://github.com/ZacharyZhangYue/FTE-Cplusplus/blob/FTE-Cplusplus/Images/setting.png" alt="Program Output" width="400"/>

* Download the files from this repo and upzip it in your local
* Open `AD/AD.sln` by VisualStudio
* Build the solution (either in Debug or Release Mode)

### Executing program

* In VisualStudio, press CTRL + F5, or
* Open the AD.exe file through your command line
```
.\Debug\AD.exe
```

## Program Output

The program was tested on function:
```math
f(x) := 5 + x^3 - \frac{\log(g(x)}{x- 4}
```
```math
g(x) := (x^2 - 5)(4-3x)
```

The AD results was compared with finite-difference results 
```math
f'(x) \approx \frac{f(x + e) - f(x - e)}{2 e}
```

```cpp

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

```



<img src="https://github.com/ZacharyZhangYue/FTE-Cplusplus/blob/FTE-Cplusplus/Images/output.png" alt="Program Output" width="400"/>

## Reference

* [Wikipedia-AutoDiff](https://en.wikipedia.org/wiki/Automatic_differentiation)
