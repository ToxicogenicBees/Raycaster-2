/*
    Mat4x4.hpp

    Declaration of a 4x4 matrix.
*/

#pragma once

#include "foundation/containers/Grid.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"
#include <string>

namespace toxico {
    class Mat4x4 {
    private:
        Grid<fp_type> data_;

    public:
        static const std::size_t size = 4;
        
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
         * @brief Creates the desired 2D translation matrix.
         * 
         * @param translation The desired translation offset.
         * @return The desired 2D transformation matrix.
         */
        static Mat4x4 translation(const Vector3& translation);

        /**
         * @brief Creates the desired 2D rotation matrix.
         * 
         * @param rotation The desired X rotation offset (in radians).
         * @return The desired 2D transformation matrix.
         */
        static Mat4x4 rotationX(fp_type rotation);

        /**
         * @brief Creates the desired 2D rotation matrix.
         * 
         * @param rotation The desired Y rotation offset (in radians).
         * @return The desired 2D transformation matrix.
         */
        static Mat4x4 rotationY(fp_type rotation);

        /**
         * @brief Creates the desired 2D rotation matrix.
         * 
         * @param rotation The desired Z rotation offset (in radians).
         * @return The desired 2D transformation matrix.
         */
        static Mat4x4 rotationZ(fp_type rotation);

        /**
         * @brief Creates the desired 2D rotation matrix.
         * 
         * @param rot_x The desired X rotation offset (in radians).
         * @param rot_y The desired Y rotation offset (in radians).
         * @param rot_z The desired Z rotation offset (in radians).
         * @return The desired 2D transformation matrix.
         */
        static Mat4x4 rotationXYZ(fp_type rot_x, fp_type rot_y,fp_type rot_z) noexcept;

        /**
         * @brief Creates the desired 2D scaling matrix.
         * 
         * @param scale The desired scale offset.
         * @return The desired 2D transformation matrix.
         */
        static Mat4x4 scale(const Vector3& scale) noexcept;

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
         * @brief Applies this transformation to a homogeneous point in space.
         * 
         * @param point The homogeneous point in space being transformed.
         * @return The transformed point.
         */
        Vector4 apply(const Vector4& point) const;

        /**
         * @brief Applies this transformation to a point in space.
         * 
         * @param point The point in space being transformed.
         * @return The transformed point.
         */
        Vector3 apply(const Vector3& point) const;
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
