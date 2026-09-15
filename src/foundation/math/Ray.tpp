/*
    Ray.tpp

    Template implementation of a simple ray class.
*/

#include <format>

namespace toxico {
    template<std::size_t N>
    constexpr Ray<N>::Ray(const Vector<fp_type, N>& origin, const Vector<fp_type, N>& direction)
        : origin(origin),
          direction(direction)
    {}

    template<std::size_t N>
    constexpr Ray<N>::Ray(const Vector<fp_type, N>& direction)
        : direction(direction) {}

    template<std::size_t N>
    constexpr fp_type Ray<N>::length() const {
        return direction.magnitude();
    }

    template<std::size_t N>
    constexpr Ray<N> Ray<N>::unit() const {
        return Ray<N>{
            origin,
            direction.normal()
        };
    }

    template<std::size_t N>
    constexpr Vector<fp_type, N> Ray<N>::end() const {
        return origin + direction;
    }
}
