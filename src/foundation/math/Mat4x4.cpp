/*
    Mat4x4.cpp

    Implementation of a 4x4 matrix.
*/

#include "foundation/math/Mat4x4.hpp"
#include "foundation/geometry/Size.hpp"
#include <stdexcept>
#include <limits>
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
        catch(const std::out_of_range&) {
            throw std::out_of_range("Accessed matrix out of range");
        }
    }

    fp_type& Mat4x4::at(std::size_t row, std::size_t col) {
        try {
            return data_.at(row, col);
        }
        catch(const std::out_of_range&) {
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
    
    Vector4 Mat4x4::row(std::size_t index) const {
        return Vector4{
            at(index, 0),
            at(index, 1),
            at(index, 2),
            at(index, 3),
        };
    }

    Vector4 Mat4x4::column(std::size_t index) const {
        return Vector4{
            at(0, index),
            at(1, index),
            at(2, index),
            at(3, index),
        };
    }

    Mat4x4 Mat4x4::transpose() const {
        Mat4x4 result;
        for (std::size_t i = 0; i < Mat4x4::size; ++i) {
            for (std::size_t j = 0; j < Mat4x4::size; ++j)
                result(i, j) = (*this)(j, i);
        }
        return result;
    }

    Mat4x4 Mat4x4::inverse() const {
        Mat4x4 result = Mat4x4::identity();
        Mat4x4 working = *this;

        for (std::size_t col = 0; col < size; ++col) {
            // Find the row with the largest pivot
            std::size_t pivot_row = col;
            fp_type pivot_value = std::abs(working(col, col));

            for (std::size_t row = col + 1; row < size; ++row) {
                const fp_type value = std::abs(working(row, col));

                if (value > pivot_value) {
                    pivot_value = value;
                    pivot_row = row;
                }
            }

            // Matrix is singular
            if (pivot_value <= std::numeric_limits<fp_type>::epsilon())
                throw std::runtime_error("Matrix is not invertible");

            // Move the pivot row into position
            if (pivot_row != col) {
                for (std::size_t j = 0; j < size; ++j) {
                    std::swap(working(col, j), working(pivot_row, j));
                    std::swap(result(col, j), result(pivot_row, j));
                }
            }

            // Normalize the pivot row
            const fp_type pivot = working(col, col);
            for (std::size_t j = 0; j < size; ++j) {
                working(col, j) /= pivot;
                result(col, j) /= pivot;
            }

            // Eliminate this column from every other row
            for (std::size_t row = 0; row < size; ++row) {
                if (row == col)
                    continue;

                const fp_type factor = working(row, col);
                if (factor == fp_type{0})
                    continue;

                for (std::size_t j = 0; j < size; ++j) {
                    working(row, j) -= factor * working(col, j);
                    result(row, j) -= factor * result(col, j);
                }
            }
        }

        return result;
    }

    Mat4x4::const_iterator Mat4x4::cbegin() const noexcept {
        return data_.cbegin();
    }

    Mat4x4::const_iterator Mat4x4::begin() const noexcept {
        return data_.begin();
    }

    Mat4x4::iterator Mat4x4::begin() noexcept {
        return data_.begin();
    }

    Mat4x4::const_iterator Mat4x4::cend() const noexcept {
        return data_.cend();
    }

    Mat4x4::const_iterator Mat4x4::end() const noexcept {
        return data_.end();
    }

    Mat4x4::iterator Mat4x4::end() noexcept {
        return data_.end();
    }
}
