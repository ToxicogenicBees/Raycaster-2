/*
    IGeometry.hpp

    An interface for a renderable geometry.
*/

#pragma once

#include "tracing/utility/GeometryTrace.hpp"
#include "foundation/geometry/AABB.hpp"
#include "foundation/math/Ray.hpp"
#include <optional>

namespace toxico {
    class IGeometry {
    public:
        /**
         * @brief Gets the collision between a ray and this geometry.
         * 
         * @param local_ray A ray in this geometry's local space.
         * @return Information about the collision, or std::nullopt if there was no collision.
         */
        virtual std::optional<GeometryTrace> intersection(const Ray3& local_ray) const = 0;

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
