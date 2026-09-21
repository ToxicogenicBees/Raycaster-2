/*
    PlaneGeometry.hpp

    Declaration for the geometry of a plane.
*/

#pragma once

#include "scene/geometry/interfaces/IGeometry.hpp"
#include "tracing/utility/GeometryTrace.hpp"
#include "foundation/geometry/AABB.hpp"
#include "foundation/math/Ray.hpp"
#include <optional>

namespace toxico {
    // Plane centered at the origin with a +Y-axis normal
    class PlaneGeometry final : public IGeometry {
    private:
        // Unbounded bounds
        AABB bounds_;

    public:
        /**
         * @brief Gets the collision between a ray and this geometry.
         * 
         * @param local_ray A ray in this geometry's local space.
         * @return Information about the collision, or std::nullopt if there was no collision.
         */
        std::optional<GeometryTrace> intersection(const Ray3& local_ray) const final;

        /**
         * @brief Gets an AABB for this geometry in local-space.
         * 
         * @return An AABB for this geometry in local-space.
         */
        const AABB& bounds() const final;
    };
}
