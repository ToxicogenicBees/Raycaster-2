/*
    Vector.hpp

    Declaration of a mathematical vector class.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include <initializer_list>
#include <concepts>
#include <cstddef>
#include <ostream>
#include <array>

namespace toxico {
    template<typename T, std::size_t N>
    requires std::is_arithmetic_v<T>
    struct VectorStorage {
        T data[N];
    };

    template<typename T>
    struct VectorStorage<T, 2> {
        union {
            struct {
                T x;
                T y;
            };
            T data[2];
        };
    };

    template<typename T>
    struct VectorStorage<T, 3> {
        union {
            struct {
                T x;
                T y;
                T z;
            };
            T data[3];
        };
    };

    template<typename T>
    struct VectorStorage<T, 4> {
        union {
            struct {
                T x;
                T y;
                T z;
                T w;
            };
            T data[4];
        };
    };

    template<typename T, std::size_t N>
    struct Vector : VectorStorage<T, N> {
        using const_iterator = const T*;
        using iterator = T*;

        /**
         * @brief Constructor
         */
        constexpr Vector() = default;

        /**
         * @brief Constructor
         * 
         * @param params An initializer list of axis values.
         */
        constexpr Vector(const std::initializer_list<T>& params);

        /**
         * @brief Constructor
         * 
         * @param params A list of axis values.
         */
        template<typename... Args>
        requires (sizeof...(Args) == N && (std::convertible_to<Args, T> && ...))
        constexpr Vector(Args&&... args);
        
        /**
         * @brief Copy constructor
         * 
         * @param v The vector being copied
         */
        template<typename U>
        constexpr Vector(const Vector<U, N>& v);
        
        /**
         * @brief Gets a vector where all entries are zero-initialized
         * 
         * @return A vector where all entries are zero-initialized
         */
        static constexpr Vector<T, N> zero();

        /**
         * @brief Gets a vector where all entries are one-initialized
         * 
         * @return A vector where all entries are one-initialized
         */
        static constexpr Vector<T, N> one();

        /**
         * @brief Gets a unit vector pointing in the positive x-axis.
         * 
         * @return A unit vector pointing in the positive x-axis.
         */
        static constexpr Vector<T, N> xAxis()
            requires (N >= 1 && N <= 4);

        /**
         * @brief Gets a unit vector pointing in the positive y-axis.
         * 
         * @return A unit vector pointing in the positive y-axis.
         */
        static constexpr Vector<T, N> yAxis()
            requires (N >= 2 && N <= 4);

        /**
         * @brief Gets a unit vector pointing in the positive z-axis.
         * 
         * @return A unit vector pointing in the positive z-axis.
         */
        static constexpr Vector<T, N> zAxis()
            requires (N >= 3 && N <= 4);

        /**
         * @brief Gets a unit vector pointing in the positive w-axis.
         * 
         * @return A unit vector pointing in the positive w-axis.
         */
        static constexpr Vector<T, N> wAxis()
            requires (N == 4);

        /**
         * @brief Gets the value at the desired index.
         * 
         * @param index The desired index.
         * @return The value at that index.
         */
        constexpr const auto& operator[](std::size_t index) const;
        constexpr auto& operator[](std::size_t index);

        /**
         * @brief Add this vector to another vector
         * 
         * @param v The other vector being added by
         * @return The resulting vector
         */
        template<typename U>
        constexpr auto operator+(const Vector<U, N>& v) const;

        /**
         * @brief Subtract this vector to another vector
         * 
         * @param v The other vector being subtracted by
         * @return The resulting vector
         */
        template<typename U>
        constexpr auto operator-(const Vector<U, N>& v) const;

        /**
         * @brief Unary negate the components of this vector
         * 
         * @return The resulting vector
         */
        constexpr Vector<T, N> operator-() const;

        /**
         * @brief Multiply this vector to a scalar
         * 
         * @param s The scalar being multiplied by
         * @return The resulting vector
         */
        template<typename S>
        requires std::is_arithmetic_v<S>
        constexpr auto operator*(S s) const;

        /**
         * @brief Divide this vector to a scalar
         * 
         * @param v The scalar being divided by
         * @return The resulting vector
         */
        template<typename S>
        requires std::is_arithmetic_v<S>
        constexpr auto operator/(S s) const;

        /**
         * @brief Add another vector into this vector
         * 
         * @param v The vector being added by
         * @return A reference to this vector
         */
        constexpr Vector<T, N>& operator+=(const Vector<T, N>& v);

        /**
         * @brief Subtract another vector into this vector
         * 
         * @param v The vector being subtracted by
         * @return A reference to this vector
         */
        constexpr Vector<T, N>& operator-=(const Vector<T, N>& v);

        /**
         * @brief Multiply a scalar into this vector
         * 
         * @param s The scalar being multiplied by
         * @return A reference to this vector
         */
        constexpr Vector<T, N>& operator*=(T s);

        /**
         * @brief Divide a scalar into this vector
         * 
         * @param s The scalar being divided by
         * @return A reference to this vector
         */
        constexpr Vector<T, N>& operator/=(T s);

        /**
         * @brief Compare two Vector2s
         * 
         * @param v The other Vector2 being compared
         * @return If these vectors are equal
         */
        constexpr bool operator==(const Vector<T, N>& v) const;

        /**
         * @brief Gets the dot product of this vector and another vector
         * 
         * @param v The other vector in the product
         * @return The resulting dot product
         */
        template<typename U>
        constexpr fp_type dot(const Vector<U, N>& v) const;

        /**
         * @brief Gets the dot product of this vector and another vector
         * 
         * @param v The other vector in the product
         * @return The resulting dot product
         */
        template<typename U>
        constexpr Vector<fp_type, 3> cross(const Vector<U, 3>& v) const
            requires (N == 3);

        /**
         * @brief Gets the magnitude of this vector
         * 
         * @return The resulting magnitude
         */
        constexpr fp_type magnitude() const;

        /**
         * @brief Gets the magnitude of this vector
         * 
         * @return The resulting magnitude
         */
        constexpr fp_type squaredMagnitude() const;

        /**
         * @brief Gets the normal of this vector
         * 
         * @return The resulting normal vector
         */
        constexpr Vector<fp_type, N> normal() const;

        /**
         * @brief Converts the vector to a string.
         * 
         * @return The vector as a string.
         */
        constexpr std::string toString() const;

        /**
         * @brief Gets the desired iterator for this tile's indices.
         * 
         * @return The desired iterator.
         */
        constexpr const_iterator cbegin() const;
        constexpr const_iterator begin() const;
        constexpr iterator begin();
        constexpr const_iterator cend() const;
        constexpr const_iterator end() const;
        constexpr iterator end();
    };

    using Vector2 = Vector<fp_type, 2>;
    using Vector2d = Vector<double, 2>;
    using Vector2f = Vector<float, 2>;
    using Vector2i = Vector<int, 2>;

    using Vector3 = Vector<fp_type, 3>;
    using Vector3d = Vector<double, 3>;
    using Vector3f = Vector<float, 3>;
    using Vector3i = Vector<int, 3>;
    
    using Vector4 = Vector<fp_type, 4>;
    using Vector4d = Vector<double, 4>;
    using Vector4f = Vector<float, 4>;
    using Vector4i = Vector<int, 4>;

    /**
     * @brief Multiply a vector by a scalar
     * 
     * @param v The vector being multiplied
     * @param s The scalar being multiplied
     * @return The resulting vector
     */
    template<typename T, std::size_t N, typename S>
    constexpr auto operator*(S s, const Vector<T, N>& v);
}

#include "foundation/math/Vector.tpp"
