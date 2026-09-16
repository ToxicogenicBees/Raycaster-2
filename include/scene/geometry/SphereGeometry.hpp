/*
    SphereGeometry.hpp

    Declaration for the geometry of a sphere.
*/

#pragma once

#include "scene/geometry/interfaces/IGeometry.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Ray.hpp"
#include "scene/utility/Intersection.hpp"
#include "scene/utility/AABB.hpp"
#include <optional>

namespace toxico {
    // Unit sphere centered at the origin
    class SphereGeometry final : public IGeometry {
    private:
        AABB bounds_;

    public:
        /**
         * @brief Constructor.
         */
        SphereGeometry() noexcept;

        /**
         * @brief Gets the collision between a ray and this geometry.
         * 
         * @param local_ray A ray in this geometry's local space.
         * @param t_min The minimum "time" traveled along the ray.
         * @param t_max The maximum "time" traveled along the ray.
         * @return Information about the collision, or std::nullopt if there was no collision.
         */
        std::optional<Intersection> intersection(const Ray3& local_ray, fp_type t_min, fp_type t_max) const final;

        /**
         * @brief Gets an AABB for this geometry in local-space.
         * 
         * @return An AABB for this geometry in local-space.
         */
        const AABB& bounds() const final;
    };
}
