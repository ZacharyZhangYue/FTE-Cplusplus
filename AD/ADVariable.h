#ifndef ADVARIABLE_H
#define ADVARIABLE_H

#include <iostream>
#include <type_traits>

class ADVariable {
private:
    double _value;
    double _derivative;

public:
    // Constructors
    ADVariable(double val = 0.0, double deriv = 0.0);

    // Getter methods
    double value() const;
    double derivative() const;

    // Arithmetic operations with ADVariable
    ADVariable operator+(const ADVariable& other) const;
    ADVariable operator-(const ADVariable& other) const;
    ADVariable operator*(const ADVariable& other) const;
    ADVariable operator/(const ADVariable& other) const;

    // Arithmetic operations with built-in types (right side)
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    ADVariable operator+(T other) const {
        return ADVariable(_value + other, _derivative);
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    ADVariable operator-(T other) const {
        return ADVariable(_value - other, _derivative);
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    ADVariable operator*(T other) const {
        return ADVariable(_value * other, _derivative * other);
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    ADVariable operator/(T other) const {
        return ADVariable(_value / other, _derivative / other);
    }

    // Arithmetic operations with built-in types (left side)
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    friend ADVariable operator+(T lhs, const ADVariable& rhs) {
        return ADVariable(lhs + rhs._value, rhs._derivative);
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    friend ADVariable operator-(T lhs, const ADVariable& rhs) {
        return ADVariable(lhs - rhs._value, -rhs._derivative);
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    friend ADVariable operator*(T lhs, const ADVariable& rhs) {
        return ADVariable(lhs * rhs._value, lhs * rhs._derivative);
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    friend ADVariable operator/(T lhs, const ADVariable& rhs) {
        return ADVariable(lhs / rhs._value,
                          -lhs * rhs._derivative / (rhs._value * rhs._value)
        );
    }

    // Helper function for range checking
    static void check_range(double value, double min, double max, const std::string& func_name);


    // Mathematical functions
    friend ADVariable log(const ADVariable& x);
    friend ADVariable pow(const ADVariable& x, double exponent);

    // Output formatting
    friend std::ostream& operator<<(std::ostream& os, const ADVariable& x);
};

// Helper functions
ADVariable make_variable(double value);

#endif // ADVARIABLE_H