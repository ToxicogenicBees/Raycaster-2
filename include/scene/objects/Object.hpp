/*
    Object.hpp

    Declaration of a renderable object.
*/

#pragma once

#include "scene/geometry/interfaces/IGeometry.hpp"
#include "scene/utility/Intersection.hpp"
#include "scene/utility/Transform.hpp"
#include "scene/utility/AABB.hpp"

namespace toxico {
    class Object {
    private:
        IGeometry& geometry_;
        Transform transform_;

    public:
        /**
         * @brief Constructor.
         * 
         * @param geometry The geometry for this object.
         * @param transform The transform for this object.
         */
        Object(IGeometry& geometry, const Transform& transform);

        /**
         * @brief Constructor.
         * 
         * @param geometry The geometry for this object.
         */
        Object(IGeometry& geometry);

        /**
         * @brief Gets the geometry of this object.
         * 
         * @return The geometry of this object.
         */
        const IGeometry& geometry() const noexcept;

        /**
         * @brief Gets the transform of this object.
         * 
         * @return The transform of this object.
         */
        const Transform& transform() const noexcept;
        Transform& transform() noexcept;

        /**
         * @brief Gets the collision between a ray and this object.
         * 
         * @param world_ray A ray in world-space.
         * @param t_min The minimum "time" traveled along the ray.
         * @param t_max The maximum "time" traveled along the ray.
         * @return Information about the collision, or std::nullopt if there was no collision.
         */
        std::optional<Intersection> intersection(const Ray3& world_ray, fp_type t_min, fp_type t_max) const;

        /**
         * @brief Gets an AABB for this object in world-space.
         * 
         * @return An AABB for this object in world-space.
         */
        AABB worldBounds() const noexcept;

        /**
         * @brief Destructor.
         */
        virtual ~Object() = default;
    };
}
