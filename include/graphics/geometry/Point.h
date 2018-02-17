
#pragma once

#include <algorithm>
#include <array>
#include <initializer_list>
#include <functional>
#include <sstream>
#include <type_traits>

namespace vngine {
namespace graphics {
namespace geometry {

template<typename T, unsigned int Dim,
         typename = std::enable_if_t<std::is_arithmetic<T>::value>>
class Point
{
public:
        Point() : values({0}) {}
        Point(const std::array<T, Dim>& init) : values(init) {}
        ~Point() {}

private:
        std::array<T, Dim> values; ///< dimensions for the point

        template<typename BinaryOperation>
        Point<T, Dim>& genericUnaryArith(const Point<T, Dim>& rhs, BinaryOperation o)
        {
                for (unsigned int i = 0; i < Dim; i++) {
                        values[i] = o(values[i], rhs.values[i]);
                }
                return *this;
        }

        template<typename BinaryOperation>
        Point<T, Dim>& genericUnaryArith(const T& rhs, BinaryOperation o)
        {
                std::for_each(values.begin(), values.end(), [&](T& x) { x = o(x, rhs); });
                return *this;
        }

public:
        // element-wise ops
        friend Point<T, Dim> operator+(Point<T, Dim> lhs, const Point<T, Dim>& rhs) { return lhs += rhs; }
        friend Point<T, Dim> operator-(Point<T, Dim> lhs, const Point<T, Dim>& rhs) { return lhs -= rhs; }
        friend Point<T, Dim> operator*(Point<T, Dim> lhs, const Point<T, Dim>& rhs) { return lhs *= rhs; }
        friend Point<T, Dim> operator/(Point<T, Dim> lhs, const Point<T, Dim>& rhs) { return lhs /= rhs; }
        // scalar ops
        friend Point<T, Dim> operator*(Point<T, Dim> lhs, const T& rhs) { return lhs *= rhs; }
        friend Point<T, Dim> operator/(Point<T, Dim> lhs, const T& rhs) { return lhs /= rhs; }

        // dot product
        friend T dot(const Point<T, Dim>& lhs, const Point<T, Dim>& rhs)
        {
                T sum = 0;
                for (unsigned int i = 0; i < Dim; i++) {
                        sum += lhs.values[i] * rhs.values[i];
                }
                return sum;
        }

        // element-wise ops
        Point<T, Dim>& operator+=(const Point<T, Dim>& rhs) { genericUnaryArith(rhs, std::plus<T>()); return *this; }
        Point<T, Dim>& operator-=(const Point<T, Dim>& rhs) { genericUnaryArith(rhs, std::minus<T>()); return *this; }
        Point<T, Dim>& operator*=(const Point<T, Dim>& rhs) { genericUnaryArith(rhs, std::multiplies<T>()); return *this; }
        Point<T, Dim>& operator/=(const Point<T, Dim>& rhs) { genericUnaryArith(rhs, std::divides<T>()); return *this; }
        // scalar ops
        Point<T, Dim>& operator*=(const T& rhs) { genericUnaryArith(rhs, std::multiplies<T>()); return *this; }
        Point<T, Dim>& operator/=(const T& rhs) { genericUnaryArith(rhs, std::divides<T>()); return *this; }

        // equality
        bool operator==(const Point<T, Dim>& rhs) const
        {
                for (unsigned int i = 0; i < Dim; i++) {
                        if (values[i] != rhs.values[i]) {
                                return false;
                        }
                }
                return true;
        }
        bool operator!=(const Point<T, Dim>& rhs) const
        {
                return !operator==(rhs);
        }

        // access
        T& operator[](unsigned int idx)
        {
                if (idx >= Dim) {
                        std::stringstream s;
                        s << "Index " << idx << " is out of range.";
                        throw std::out_of_range(s.str());
                }
                return values[idx];
        }

        const T& operator[](unsigned int idx) const
        {
                if (idx >= Dim) {
                        std::stringstream s;
                        s << "Index " << idx << " is out of range.";
                        throw std::out_of_range(s.str());
                }
                return values[idx];
        }

        // size
        constexpr unsigned int size() { return Dim; }

        // casting
        operator T*() { return values.data(); }

        // convenience getters/setters
        T& x() { return values[0]; } 
        T& y() { return values[1]; } 
        T& z() { return values[2]; } 
        T& w() { return values[3]; } 
        const T& x() const { return values[0]; } 
        const T& y() const { return values[1]; } 
        const T& z() const { return values[2]; } 
        const T& w() const { return values[3]; } 

        T& r() { return values[0]; } 
        T& g() { return values[1]; } 
        T& b() { return values[2]; } 
        T& a() { return values[3]; } 
        const T& r() const { return values[0]; } 
        const T& g() const { return values[1]; } 
        const T& b() const { return values[2]; } 
        const T& a() const { return values[3]; } 
};

template<typename T, unsigned int Dim,
         typename = std::enable_if_t<std::is_arithmetic<T>::value>>
using Vector = Point<T, Dim>;

} // namespace geometry
} // namespace graphics
} // namespace vngine
