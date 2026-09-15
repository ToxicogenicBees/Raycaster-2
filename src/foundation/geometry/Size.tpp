/*
    Size.tpp

    Template implementation for the Size class
*/

#include "foundation/geometry/Size.hpp"

namespace toxico {
    template<typename Scalar>
    Size operator*(const Scalar& s, Size size) {
        return {
            static_cast<std::size_t>(size.width * s),
            static_cast<std::size_t>(size.height * s),
        };
    }

    template<typename Scalar>
    Size Size::operator*(const Scalar& s) const {
        return {
            static_cast<std::size_t>(width * s),
            static_cast<std::size_t>(height * s),
        };
    }

    template<typename Scalar>
    Size& Size::operator*=(const Scalar& s) {
        width *= s;
        height *= s;
        return *this;
    }

    template<typename Scalar>
    Size operator/(const Scalar& s, Size size) {
        return {
            static_cast<std::size_t>(size.width / s),
            static_cast<std::size_t>(size.height / s),
        };
    }

    template<typename Scalar>
    Size Size::operator/(const Scalar& s) const {
        return {
            static_cast<std::size_t>(width / s),
            static_cast<std::size_t>(height / s),
        };
    }

    template<typename Scalar>
    Size& Size::operator/=(const Scalar& s) {
        width /= s;
        height /= s;
        return *this;
    }
}
