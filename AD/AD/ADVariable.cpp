#include <cmath>
#include <string>
#include "ADVariable.h"

// Constructors
ADVariable::ADVariable(double val, double deriv)
        : _value(val), _derivative(deriv) 
        {}

// Getter methods
double ADVariable::value() const { return _value; }
double ADVariable::derivative() const { return _derivative; }

// Arithmetic operations with ADVariable
ADVariable ADVariable::operator+(const ADVariable& other) const {
    return ADVariable(_value + other._value, _derivative + other._derivative);
}

ADVariable ADVariable::operator-(const ADVariable& other) const {
    return ADVariable(_value - other._value, _derivative - other._derivative);
}

ADVariable ADVariable::operator*(const ADVariable& other) const {
    return ADVariable(
        _value * other._value,
        _value * other._derivative + _derivative * other._value
    );
}

ADVariable ADVariable::operator/(const ADVariable& other) const {
    return ADVariable(
                     _value / other._value,
                     (_derivative * other._value - _value * other._derivative) /
                     (other._value * other._value)
    );
}

void ADVariable::check_range(double value, double min, double max, const std::string& func_name) {
    if (value < min || value > max) {
        throw std::domain_error(
            func_name + " argument out of range [" +
            std::to_string(min) + ", " +
            std::to_string(max) + "]: " +
            std::to_string(value)
        );
    }
}



// Natural Log: f'(x) = 1/x
ADVariable log(const ADVariable& x) {
    ADVariable::check_range(x._value, 0, INFINITY, "log");
    return ADVariable(
        std::log(x._value),
        x._derivative / x._value
    );
}

// Power: f'(x) = n * x^{n-1}
ADVariable pow(const ADVariable& x, double exponent) {
    if (x._value == 0.0 && exponent <= 0.0) {
        throw std::domain_error("pow(0, y) undefined for y <= 0");
    }
    return ADVariable(
        std::pow(x._value, exponent),
        x._derivative * exponent * std::pow(x._value, exponent - 1)
    );
}

// Output formatting
std::ostream& operator <<(std::ostream& os, const ADVariable& x) {
    os << "autodiff: " << "value: " << x._value << " (deriv: " << x._derivative << ")";
    return os;
}

// Helper functions
ADVariable make_variable(double value) {
    return ADVariable(value, 1.0);  // Variable with derivative = 1
}