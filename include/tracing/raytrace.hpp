/*
    raytrace.hpp

    Declaration of a free function to trace a ray through a scene.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include "tracing/utility/GeometryTrace.hpp"
#include "tracing/utility/SceneTrace.hpp"
#include "foundation/math/Ray.hpp"
#include "scene/Scene.hpp"
#include <optional>

namespace toxico::raytrace {
    /**
     * @brief Gets a geometry-ray intersection in world-space coordinates.
     * 
     * @param ray The ray intersecting with this geometry, in world-space coordinates.
     * @param geometry The geometry being intersected.
     * @param transform The transformation this geometry has undergone in world space.
     * @param t_min The minimum time traveled along the ray.
     * @param t_max The maxium time traveled along the ray.
     * @return The world-space intersection with this geometry, or std::nullopt if no intersection occured.
     */
    std::optional<GeometryTrace> worldIntersection(const IGeometry& geometry, const Transform& transform, const Ray3& ray, fp_type t_min, fp_type t_max);

    /**
     * @brief Gets a geometry-ray intersection in world-space coordinates.
     * 
     * @param ray The ray intersecting with this geometry, in world-space coordinates.
     * @param geometry The geometry being intersected.
     * @param transform The transformation this geometry has undergone in world space.
     * @return The world-space intersection with this geometry, or std::nullopt if no intersection occured.
     */
    std::optional<GeometryTrace> worldIntersection(const IGeometry& geometry, const Transform& transform, const Ray3& ray);

    /**
     * @brief Traces a ray through a scene over a subset of the ray's lifetime.
     * 
     * @param ray A ray being traced through the scene.
     * @param scene The scene the ray is being traced through.
     * @param t_min The minimum time traveled along the ray.
     * @param t_max The maxium time traveled along the ray.
     * @return The resulting ray-scene intersection, or std::nullopt if no intersection occured.
     */
    std::optional<SceneTrace> trace(const Ray3& ray, const Scene& scene, fp_type t_min, fp_type t_max);
    
    /**
     * @brief Traces a ray through a scene.
     * 
     * @param ray A ray being traced through the scene.
     * @param scene The scene the ray is being traced through.
     * @return The resulting ray-scene intersection, or std::nullopt if no intersection occured.
     */
    std::optional<SceneTrace> trace(const Ray3& ray, const Scene& scene);
}
