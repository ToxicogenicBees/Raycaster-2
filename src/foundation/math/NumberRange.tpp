/*
    NumberRange.cpp

    Template implementation of a range of numbers.
*/

namespace toxico {
    template<typename T>
    requires std::is_arithmetic_v<T>
    NumberRange<T>::NumberRange(T min, T max)
        : min_(min), max_(max) {}

    template<typename T>
    requires std::is_arithmetic_v<T>
    NumberRange<T>::NumberRange(T value) noexcept
        : min_(value), max_(value) {}

    template<typename T>
    requires std::is_arithmetic_v<T>
    T NumberRange<T>::min() const noexcept {
        return min_;
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    T NumberRange<T>::max() const noexcept {
        return max_;
    }
}
