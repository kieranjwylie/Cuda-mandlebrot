
#include <cmath>


#pragma once
template <typename T>
class Complex
{
    public:
        T x;
        T y;

        constexpr Complex(T real, T imag) : x(real), y(imag) {} ;

        constexpr Complex operator*(const Complex& rhs) const
        {
            return {
                x * rhs.x - y * rhs.y,
                y * rhs.x + x * rhs.y
            };
        }

        constexpr Complex operator+(const Complex& rhs) const
        {
            return {
                x + rhs.x,
                y + rhs.y
            };
        }

        double mod() const
        {
            return sqrt(x*x + y*y);
        }
};
