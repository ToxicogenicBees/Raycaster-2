/*
    Mat4x4.cpp

    Implementation of a 4x4 matrix.
*/

#include "foundation/math/Mat4x4.hpp"
#include "foundation/geometry/Size.hpp"
#include <stdexcept>
#include <cmath>

namespace toxico {
    Mat4x4::Mat4x4()
        : data_(Size{Mat4x4::size, Mat4x4::size}, 0.0, GridOrder::ColumnMajor) {}

    Mat4x4 Mat4x4::identity() {
        Mat4x4 result;

        result(0, 0) = 1;
        result(1, 1) = 1;
        result(2, 2) = 1;
        result(3, 3) = 1;

        return result;
    }

    Mat4x4 Mat4x4::translation(const Vector3& translation) {
        Mat4x4 result = Mat4x4::identity();

        result(0, 3) = translation.x;
        result(1, 3) = translation.y;
        result(2, 3) = translation.z;

        return result;
    }

    Mat4x4 Mat4x4::rotationX(fp_type rotation) {
        auto result = Mat4x4::identity();
        fp_type sin = std::sin(rotation);
        fp_type cos = std::cos(rotation);

        result(1, 1) = cos;
        result(1, 2) = -sin;
        result(2, 1) = sin;
        result(2, 2) = cos;

        return result;
    }

    Mat4x4 Mat4x4::rotationY(fp_type rotation) {
        auto result = Mat4x4::identity();
        fp_type sin = std::sin(rotation);
        fp_type cos = std::cos(rotation);

        result(0, 0) = cos;
        result(0, 2) = sin;
        result(2, 0) = -sin;
        result(2, 2) = cos;

        return result;
    }

    Mat4x4 Mat4x4::rotationZ(fp_type rotation) {
        auto result = Mat4x4::identity();
        fp_type sin = std::sin(rotation);
        fp_type cos = std::cos(rotation);

        result(0, 0) = cos;
        result(0, 1) = -sin;
        result(1, 0) = sin;
        result(1, 1) = cos;

        return result;
    }

    Mat4x4 Mat4x4::rotationXYZ(fp_type rot_x, fp_type rot_y, fp_type rot_z) noexcept {
        return Mat4x4::rotationZ(rot_z)
             * Mat4x4::rotationY(rot_y)
             * Mat4x4::rotationX(rot_x);
    }

    Mat4x4 Mat4x4::scale(const Vector3& scale) noexcept {
        auto result = Mat4x4::identity();

        result(0, 0) = scale.x;
        result(1, 1) = scale.y;
        result(2, 2) = scale.y;

        return result;
    }

    const fp_type& Mat4x4::operator()(std::size_t row, std::size_t col) const {
        return data_(row, col);
    }

    fp_type& Mat4x4::operator()(std::size_t row, std::size_t col) {
        return data_(row, col);
    }

    const fp_type& Mat4x4::at(std::size_t row, std::size_t col) const {
        try {
            return data_.at(row, col);
        }
        catch(...) {
            throw std::out_of_range("Accessed matrix out of range");
        }
    }

    fp_type& Mat4x4::at(std::size_t row, std::size_t col) {
        try {
            return data_.at(row, col);
        }
        catch(...) {
            throw std::out_of_range("Accessed matrix out of range");
        }
    }

    Mat4x4 Mat4x4::operator*(const Mat4x4& other) const {
        Mat4x4 result;

        for (std::size_t i = 0; i < Mat4x4::size; ++i) {
            for (std::size_t j = 0; j < Mat4x4::size; ++j) {
                fp_type dot = 0;
                for (std::size_t k = 0; k < Mat4x4::size; ++k)
                    dot += (*this)(i, k) * other(k, j);
                result(i, j) = dot;
            }
        }

        return result;
    }

    Mat4x4& Mat4x4::operator*=(const Mat4x4& other) {
        *this = *this * other;
        return *this;
    }

    Vector4 Mat4x4::apply(const Vector4& point) const {
        return Vector4{
            point.dot(Vector4{at(0, 0), at(0, 1), at(0, 2), at(0, 3)}),
            point.dot(Vector4{at(1, 0), at(1, 1), at(1, 2), at(1, 3)}),
            point.dot(Vector4{at(2, 0), at(2, 1), at(2, 2), at(2, 3)}),
            point.dot(Vector4{at(3, 0), at(3, 1), at(3, 2), at(3, 3)}),
        };
    }

    Vector3 Mat4x4::apply(const Vector3& point) const {
        auto transformed = apply(
            Vector4{point.x, point.y, point.z, fp_type{1.0}}
        );

        return Vector3{
            transformed.x / transformed.w,
            transformed.y / transformed.w,
            transformed.z / transformed.w
        };
    }
}
