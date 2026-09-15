/*
    Ray.hpp

    Declaration of a simple ray class.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"
#include <string>

namespace toxico {
    template<std::size_t N>
    struct Ray {
        Vector<fp_type, N> direction{Vector<fp_type, N>::zero()};
        Vector<fp_type, N> origin{Vector<fp_type, N>::zero()};

        /**
         * @brief Constructor.
         * 
         * @param origin The origin of the ray.
         * @param direction The direction of the ray.
         */
        constexpr Ray(const Vector<fp_type, N>& origin, const Vector<fp_type, N>& direction);

        /**
         * @brief Constructor.
         *        Assumes the ray origin is at the world origin.
         * 
         * @param direction The direction of the ray.
         */
        constexpr Ray(const Vector<fp_type, N>& direction);

        /**
         * @brief Constructor.
         */
        constexpr Ray() = default;

        /**
         * @brief Gets the length of the ray.
         * 
         * @return The length of the ray.
         */
        constexpr fp_type length() const;

        /**
         * @brief Gets this ray as a unit ray.
         * 
         * @return The resulting unit ray.
         */
        constexpr Ray<N> unit() const;

        /**
         * @brief Gets a location along the ray.
         * 
         * @param t The "time" traveled along the ray.
         */
        constexpr Vector<fp_type, N> at(fp_type t) const;
    };

    using Ray2 = Ray<2>;
    using Ray3 = Ray<3>;
}

#include "foundation/math/Ray.tpp"
