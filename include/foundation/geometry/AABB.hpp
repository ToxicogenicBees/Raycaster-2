/*
    AABB.hpp

    Declaration of an axis-alligned bounding box.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"
#include "foundation/math/Ray.hpp"
#include <concepts>
#include <limits>

namespace toxico {
    class AABB {
    private:
        Vector3 min_;
        Vector3 max_;

    public:
        /**
         * @brief Constructor.
         * 
         * @param points A set of points composing this bounding box.
         */
        template<typename... Points>
            requires (std::same_as<Points, Vector3> && ...)
        explicit AABB(const Points&... points) noexcept;

        /**
         * @brief Constructor.
         * 
         * Creates a bounding box containing nothing.
         */
        AABB() noexcept;

        /**
         * @brief Adds a point to this bounding box.
         * 
         * @param point The point being added.
         */
        void expand(const Vector3& point) noexcept;

        /**
         * @brief Adds another bounding box to this bounding box.
         * 
         * @param bounds The bounding box being added.
         */
        void expand(const AABB& bounds) noexcept;

        /**
         * @brief Gets if a ray collides with this AABB.
         * 
         * @param ray The ray being tested against this AABB.
         * @param t_min The minimum "time" traveled along the ray.
         * @param t_max The maximum "time" traveled along the ray.
         * @return The intersection point of the collision, or std::nullopt if no collision occured.
         */
        bool intersects(
            const Ray3& ray,
            fp_type t_min = std::numeric_limits<fp_type>::min(),
            fp_type t_max = std::numeric_limits<fp_type>::max()
        ) const noexcept;

        /**
         * @brief Gets the lower bound for this AABB.
         * 
         * @return The lower bound.
         */
        const Vector3& lowerBound() const noexcept;

        /**
         * @brief Gets the upper bound for this AABB.
         * 
         * @return The upper bound.
         */
        const Vector3& upperBound() const noexcept;
    };
}

#include "foundation/geometry/AABB.tpp"
