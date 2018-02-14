
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
        Point(T init[Dim]) : values(init) {}
        ~Point() {}

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
        Point<T, Dim>& operator+=(const Point<T, Dim>& rhs) { return genericUnaryArith<std::plus>(rhs); }
        Point<T, Dim>& operator-=(const Point<T, Dim>& rhs) { return genericUnaryArith<std::minus>(rhs); }
        Point<T, Dim>& operator*=(const Point<T, Dim>& rhs) { return genericUnaryArith<std::multiplies>(rhs); }
        Point<T, Dim>& operator/=(const Point<T, Dim>& rhs) { return genericUnaryArith<std::divides>(rhs); }
        // scalar ops
        Point<T, Dim>& operator*=(const T& rhs) { return genericUnaryArith<std::multiplies>(rhs); }
        Point<T, Dim>& operator/=(const T& rhs) { return genericUnaryArith<std::divides>(rhs); }

        // equality
        bool operator==(const Point<T, Dim>& rhs)
        {
                for (unsigned int i = 0; i < Dim; i++) {
                        if (values[i] != rhs.values[i]) {
                                return false;
                        }
                }
                return true;
        }
        bool operator!=(const Point<T, Dim>& rhs)
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
        T& x() { return *this[0]; } 
        T& y() { return *this[1]; } 
        T& z() { return *this[2]; } 
        T& w() { return *this[3]; } 
        const T& x() const { return *this[0]; } 
        const T& y() const { return *this[1]; } 
        const T& z() const { return *this[2]; } 
        const T& w() const { return *this[3]; } 

        T& r() { return *this[0]; } 
        T& g() { return *this[1]; } 
        T& b() { return *this[2]; } 
        T& a() { return *this[3]; } 
        const T& r() const { return *this[0]; } 
        const T& g() const { return *this[1]; } 
        const T& b() const { return *this[2]; } 
        const T& a() const { return *this[3]; } 

private:
        std::array<T, Dim> values; ///< dimensions for the point

        template<typename Op>
        Point<T, Dim> genericUnaryArith(const Point<T, Dim>& rhs)
        {
                Op o;
                for (unsigned int i = 0; i < Dim; i++) {
                        values[i] = o(values[i], rhs.values[i]);
                }
                return *this;
        }

        template<typename Op>
        Point<T, Dim> genericUnaryArith(const T& rhs)
        {
                std::for_each(values.begin(), values.end(), [&](T& x) { Op o; x = o(x, rhs); });
                return *this;
        }
};

template<typename T, unsigned int Dim,
         typename = std::enable_if_t<std::is_arithmetic<T>::value>>
using Vector = Point<T, Dim>;

} // namespace geometry
} // namespace graphics
} // namespace vngine
