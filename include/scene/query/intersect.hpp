/*
    intersect.hpp

    Declaration of a free function to get the intersection of a ray with a transformed geometry.
*/

#pragma once

#include "scene/geometry/interfaces/IGeometry.hpp"
#include "foundation/geometry/Transform.hpp"
#include "foundation/utility/fp_type.hpp"
#include "scene/query/Intersection.hpp"
#include "foundation/math/Ray.hpp"

namespace toxico::intersection {
    /**
     * @brief Gets the intersection between a ray and a transformed geometry, within a given time range.
     * 
     * @param geometry The geometry being intersected.
     * @param transform The transformation this geometry has in space.
     * @param ray A ray in world coordinates.
     * @param t_min The minimum time traveled along the ray.
     * @param t_max The maxium time traveled along the ray.
     * @return The result of the intersection, or std::nullopt if no intersection occured.
     */
    std::optional<Intersection> intersect(const IGeometry& geometry, const Transform& transform, const Ray3& ray, fp_type t_min, fp_type t_max);
    
    /**
     * @brief Gets the intersection between a ray and a transformed geometry.
     * 
     * @param geometry The geometry being intersected.
     * @param transform The transformation this geometry has in space.
     * @param ray A ray in world coordinates.
     * @return The result of the intersection, or std::nullopt if no intersection occured.
     */
    std::optional<Intersection> intersect(const IGeometry& geometry, const Transform& transform, const Ray3& ray);
}
