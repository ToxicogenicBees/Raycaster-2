/*
    Mat4x4.hpp

    Declaration of a 4x4 matrix.
*/

#pragma once

#include "foundation/containers/Grid.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"

namespace toxico {
    class Mat4x4 {
    private:
        Grid<fp_type> data_;

    public:
        static const std::size_t size = 4;

        using const_iterator = Grid<fp_type>::const_iterator;
        using iterator = Grid<fp_type>::iterator;
        
        /**
         * @brief Constructor.
         */
        Mat4x4();

        /**
         * @brief Creates an identity matrix.
         * 
         * @return An identity matrix.
         */
        static Mat4x4 identity();

        /**
         * @brief Access an element in the matrix.
         * 
         * @param row The desired row.
         * @param col The desired column.
         * @return The element in the matrix.
         */
        const fp_type& operator()(std::size_t row, std::size_t col) const;

        /**
         * @brief Access an element in the matrix.
         * 
         * @param row The desired row.
         * @param col The desired column.
         * @return The element in the matrix.
         */
        fp_type& operator()(std::size_t row, std::size_t col);

        /**
         * @brief Access an element in the matrix.
         *        Throws an out of bounds error if indexed out of bounds.
         * 
         * @param row The desired row.
         * @param col The desired column.
         * @return The element in the matrix.
         */
        const fp_type& at(std::size_t row, std::size_t col) const;

        /**
         * @brief Access an element in the matrix.
         *        Throws an out of bounds error if indexed out of bounds.
         * 
         * @param row The desired row.
         * @param col The desired column.
         * @return The element in the matrix.
         */
        fp_type& at(std::size_t row, std::size_t col);

        /**
         * @brief Multiply two matrices
         * 
         * @param other The other matrix being multiplied by.
         * @return The resulting matrix.
         */
        Mat4x4 operator*(const Mat4x4& other) const;

        /**
         * @brief Multiply two matrices
         * 
         * @param other The other matrix being multiplied to this one.
         * @return A reference to this modified matrix.
         */
        Mat4x4& operator*=(const Mat4x4& other);

        /**
         * @brief Multiply this matrix by a scalar.
         * 
         * @param s The scalar being multiplied by.
         * @return The resulting matrix.
         */
        template<typename T>
        requires std::is_arithmetic_v<T>
        Mat4x4 operator*(T s) const;

        /**
         * @brief Multiply this matrix by a scalar.
         * 
         * @param s The scalar being multiplied by.
         * @return A reference to this modified matrix.
         */
        template<typename T>
        requires std::is_arithmetic_v<T>
        Mat4x4& operator*=(T s);

        /**
         * @brief Divide this matrix by a scalar.
         * 
         * @param s The scalar being divided by.
         * @return The resulting matrix.
         */
        template<typename T>
        requires std::is_arithmetic_v<T>
        Mat4x4 operator/(T s) const;

        /**
         * @brief Divide this matrix by a scalar.
         * 
         * @param s The scalar being divided by.
         * @return A reference to this modified matrix.
         */
        template<typename T>
        requires std::is_arithmetic_v<T>
        Mat4x4& operator/=(T s);

        /**
         * @brief Gets the transpose of this matrix.
         * 
         * @return The transpose of this matrix.
         */
        Mat4x4 transpose() const;

        /**
         * @brief Gets the inverse of this matrix.
         * 
         * @return The inverse of this matrix.
         */
        Mat4x4 inverse() const;

        /**
         * @brief Gets the desired iterator for this matrix's data.
         * 
         * @return The desired iterator.
         */
        const_iterator cbegin() const noexcept;
        const_iterator begin() const noexcept;
        iterator begin() noexcept;
        const_iterator cend() const noexcept;
        const_iterator end() const noexcept;
        iterator end() noexcept;
    };

    /**
     * @brief Multiply a matrix by a scalar.
     * 
     * @param s The scalar being multiplied by.
     * @return The modified matrix.
     */
    template<typename T>
    requires std::is_arithmetic_v<T>
    Mat4x4 operator*(T s, const Mat4x4& mat);
}

#include "foundation/math/Mat4x4.tpp"
