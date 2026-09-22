/*
    AABB.hpp

    Declaration of an axis-alligned bounding box.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include "foundation/math/NumberRange.hpp"
#include "foundation/math/Vector.hpp"
#include "foundation/math/Ray.hpp"
#include <optional>
#include <concepts>

namespace toxico {
    class AABB {
    private:
        std::optional<Vector3> min_;
        std::optional<Vector3> max_;

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
         * Creates a bounding box containing nothing (boundless).
         */
        AABB() noexcept = default;

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
         * @brief Gets if a ray collides with this AABB over a range of the ray's lifetime.
         * 
         * @param ray The ray being tested against this AABB.
         * @param t The range of time traveled along the ray.
         * @return The intersection point of the collision, or std::nullopt if no collision occured.
         */
        bool intersects(const Ray3& ray, NumberRange<fp_type> t) const noexcept;

        /**
         * @brief Gets if a ray collides with this AABB.
         * 
         * @param ray The ray being tested against this AABB.
         * @return The intersection point of the collision, or std::nullopt if no collision occured.
         */
        bool intersects(const Ray3& ray) const noexcept;

        /**
         * @brief Gets the lower bound for this AABB.
         * 
         * @return The lower bound.
         */
        Vector3 lowerBound() const noexcept;

        /**
         * @brief Gets the upper bound for this AABB.
         * 
         * @return The upper bound.
         */
        Vector3 upperBound() const noexcept;

        /**
         * @brief Gets if the AABB is boundless.
         * 
         * @return If the AABB is boundless.
         */
        bool boundless() const noexcept;
    };
}

#include "foundation/geometry/AABB.tpp"
