/*
    IGeometry.hpp

    An interface for a renderable geometry.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Ray.hpp"
#include "scene/utility/Intersection.hpp"
#include "scene/utility/AABB.hpp"
#include <optional>

namespace toxico {
    class IGeometry {
    public:
        /**
         * @brief Gets the collision between a ray and this geometry.
         * 
         * @param local_ray A ray in this geometry's local space.
         * @param t_min The minimum "time" traveled along the ray.
         * @param t_max The maximum "time" traveled along the ray.
         * @return Information about the collision, or std::nullopt if there was no collision.
         */
        virtual std::optional<Intersection> intersection(const Ray3& local_ray, fp_type t_min, fp_type t_max) const = 0;

        /**
         * @brief Gets an AABB for this geometry in local-space.
         * 
         * @return An AABB for this geometry in local-space.
         */
        virtual const AABB& bounds() const = 0;

        /**
         * @brief Destructor.
         */
        virtual ~IGeometry() = default;
    };
}
