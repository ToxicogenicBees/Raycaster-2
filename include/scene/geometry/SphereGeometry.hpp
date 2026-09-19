/*
    SphereGeometry.hpp

    Declaration for the geometry of a sphere.
*/

#pragma once

#include "scene/geometry/interfaces/IGeometry.hpp"
#include "scene/query/GeometryInteraction.hpp"
#include "foundation/geometry/AABB.hpp"
#include "foundation/math/Ray.hpp"
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
         * @return Information about the collision, or std::nullopt if there was no collision.
         */
        std::optional<GeometryInteraction> intersection(const Ray3& local_ray) const final;

        /**
         * @brief Gets an AABB for this geometry in local-space.
         * 
         * @return An AABB for this geometry in local-space.
         */
        const AABB& bounds() const final;
    };
}
