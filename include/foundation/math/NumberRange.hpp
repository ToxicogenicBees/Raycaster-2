/*
    NumberRange.hpp

    Declaration of a range of numbers.
*/

#pragma once

#include <type_traits>

namespace toxico {
    template<typename T>
    requires std::is_arithmetic_v<T>
    class NumberRange {
    private:
        T min_;
        T max_;

    public:
        /**
         * @brief Constructor.
         * 
         * @param min The minimum value in the range.
         * @param max The maximum value in the range.
         * 
         * Throws an exception if the minimum range is larger than the maximum.
         */
        NumberRange(T min, T max);

        /**
         * @brief Constructor.
         * 
         * @param value The value for both fields of the range.
         */
        NumberRange(T value) noexcept;

        /**
         * @brief Gets the minimum value in the range.
         * 
         * @return The minimum value in the range.
         */
        T min() const noexcept;

        /**
         * @brief Gets the maximum value in the range.
         * 
         * @return The maximum value in the range.
         */
        T max() const noexcept;
    };
}

#include "foundation/math/NumberRange.tpp"
