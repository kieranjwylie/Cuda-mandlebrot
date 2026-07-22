
#include <cmath>


#pragma once
template <typename T>
class Complex
{
    public:
        T x;
        T y;

        __device__
        constexpr Complex(T real, T imag) : x(real), y(imag) {} ;

        __device__
        constexpr Complex operator*(const Complex& rhs) const
        {
            return {
                x * rhs.x - y * rhs.y,
                y * rhs.x + x * rhs.y
            };
        }

        __device__
        constexpr Complex operator+(const Complex& rhs) const
        {
            return {
                x + rhs.x,
                y + rhs.y
            };
        }

        __device__
        
        double mod() const
        {
            return sqrt(x*x + y*y);
        }
};
