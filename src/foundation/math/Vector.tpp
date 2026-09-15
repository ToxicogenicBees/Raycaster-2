/*
    Vector.hpp

    Declaration of a mathematical vector class.
*/

#include <initializer_list>
#include <type_traits>
#include <cstddef>
#include <ostream>
#include <array>
#include <cmath>

namespace toxico {
    template<typename T, std::size_t N>
    constexpr Vector<T, N>::Vector(const std::initializer_list<T>& params) {
        if (params.size() != N)
            throw std::invalid_argument("Vector initializer list has incorrect size");

        ssize_t i = 0;
        for (const T& value : params)
            (*this)[i++] = value;
    }

    template<typename T, std::size_t N>
    template<typename... Args>
    requires (sizeof...(Args) == N && (std::convertible_to<Args, T> && ...))
    constexpr Vector<T, N>::Vector(Args&&... args) {
        std::size_t i = 0;
        ((this->operator[](i++) = static_cast<T>(std::forward<Args>(args))), ...);
    }
    
    template<typename T, std::size_t N>
    template<typename U>
    constexpr Vector<T, N>::Vector(const Vector<U, N>& v) {
        for (std::size_t i = 0; i < N; ++i)
            (*this)[i] = static_cast<T>(v[i]);
    }
    
    template<typename T, std::size_t N>
    constexpr Vector<T, N> Vector<T, N>::zero() {
        Vector<T, N> result;
        for (auto& val : result.data)
            val = 0;
        return result;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N> Vector<T, N>::one() {
        Vector<T, N> result;
        for (auto& val : result.data)
            val = 1;
        return result;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N> Vector<T, N>::xAxis()
        requires (N >= 1 && N <= 4)
    {
        auto result = Vector<T, N>::zero();
        result.x = 1;
        return result;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N> Vector<T, N>::yAxis()
        requires (N >= 2 && N <= 4)
    {
        auto result = Vector<T, N>::zero();
        result.y = 1;
        return result;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N> Vector<T, N>::zAxis()
        requires (N >= 3 && N <= 4)
    {
        auto result = Vector<T, N>::zero();
        result.z = 1;
        return result;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N> Vector<T, N>::wAxis()
        requires (N == 4)
    {
        auto result = Vector<T, N>::zero();
        result.w = 1;
        return result;
    }

    template<typename T, std::size_t N>
    constexpr const auto& Vector<T, N>::operator[](std::size_t index) const {
        return this->data[index];
    }

    template<typename T, std::size_t N>
    constexpr auto& Vector<T, N>::operator[](std::size_t index) {
        return this->data[index];
    }

    template<typename T, std::size_t N>
    template<typename U>
    constexpr auto Vector<T, N>::operator+(const Vector<U, N>& v) const {
        auto result = *this;
        for (std::size_t i = 0; i < N; ++i)
            result[i] += v[i];
        return result;
    }

    template<typename T, std::size_t N>
    template<typename U>
    constexpr auto Vector<T, N>::operator-(const Vector<U, N>& v) const {
        auto result = *this;
        for (std::size_t i = 0; i < N; ++i)
            result[i] -= v[i];
        return result;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N> Vector<T, N>::operator-() const {
        auto result = *this;
        for (auto& val : result)
            val = -val;
        return result;
    }

    template<typename T, std::size_t N>
    template<typename S>
    requires std::is_arithmetic_v<S>
    constexpr auto Vector<T, N>::operator*(S s) const {
        auto result = *this;
        for (auto& val : result)
            val *= s;
        return result;
    }

    template<typename T, std::size_t N>
    template<typename S>
    requires std::is_arithmetic_v<S>
    constexpr auto Vector<T, N>::operator/(S s) const {
        auto result = *this;
        for (auto& val : result)
            val /= s;
        return result;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N>& Vector<T, N>::operator+=(const Vector<T, N>& v) {
        for (std::size_t i = 0; i < N; ++i)
            (*this)[i] += v[i];
        return *this;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N>& Vector<T, N>::operator-=(const Vector<T, N>& v) {
        for (std::size_t i = 0; i < N; ++i)
            (*this)[i] -= v[i];
        return *this;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N>& Vector<T, N>::operator*=(T s) {
        for (std::size_t i = 0; i < N; ++i)
            (*this)[i] *= s;
        return *this;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N>& Vector<T, N>::operator/=(T s) {
        for (std::size_t i = 0; i < N; ++i)
            (*this)[i] /= s;
        return *this;
    }

    template<typename T, std::size_t N>
    constexpr bool Vector<T, N>::operator==(const Vector<T, N>& v) const {
        for (std::size_t i = 0; i < N; ++i) {
            if ((*this)[i] != v[i])
                return false;
        }
        return true;
    }

    template<typename T, std::size_t N>
    template<typename U>
    constexpr fp_type Vector<T, N>::dot(const Vector<U, N>& v) const {
        fp_type sum = 0;
        for (std::size_t i = 0; i < N; ++i)
            sum += static_cast<fp_type>((*this)[i]) * static_cast<fp_type>(v[i]);
        return sum;
    }

    template<typename T, std::size_t N>
    template<typename U>
    constexpr Vector<fp_type, 3> Vector<T, N>::cross(const Vector<U, 3>& v) const
        requires (N == 3)
    {
        Vector<fp_type, 3> result;

        result[0] = static_cast<fp_type>(this->y) * static_cast<fp_type>(v.z) - static_cast<fp_type>(this->z) * static_cast<fp_type>(v.y);
        result[1] = static_cast<fp_type>(this->z) * static_cast<fp_type>(v.x) - static_cast<fp_type>(this->x) * static_cast<fp_type>(v.z);
        result[2] = static_cast<fp_type>(this->x) * static_cast<fp_type>(v.y) - static_cast<fp_type>(this->y) * static_cast<fp_type>(v.x);

        return result;
    }

    template<typename T, std::size_t N>
    constexpr fp_type Vector<T, N>::magnitude() const {
        auto squared_mag = dot(*this);
        return std::sqrt(squared_mag);
    }

    template<typename T, std::size_t N>
    constexpr fp_type Vector<T, N>::squaredMagnitude() const {
        return dot(*this);
    }

    template<typename T, std::size_t N>
    constexpr Vector<fp_type, N> Vector<T, N>::normal() const {
        auto mag = magnitude();
        if (mag <= 1e-8)
            return Vector<fp_type, N>::zero();

        return *this / mag;
    }
    
    template<typename T, std::size_t N>
    constexpr std::string Vector<T, N>::toString() const {
        std::string str = "(";
        if (N >= 1)
            str += this->data[0];
        for (std::size_t i = 1; i < N; ++i)
            str += " " + this->data[i];
        return str;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N>::const_iterator Vector<T, N>::cbegin() const {
        return this->data;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N>::const_iterator Vector<T, N>::begin() const {
        return this->data;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N>::iterator Vector<T, N>::begin() {
        return this->data;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N>::const_iterator Vector<T, N>::cend() const {
        return this->data + N;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N>::const_iterator Vector<T, N>::end() const {
        return this->data + N;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N>::iterator Vector<T, N>::end() {
        return this->data + N;
    }

    template<typename T, std::size_t N, typename S>
    constexpr auto operator*(S s, const Vector<T, N>& v) {
        auto result = v;
        for (auto& val : result)
            val /= s;
        return result;
    }
}
