/*
    Scene.cpp

    Declaration of a scene of objects, lights, and geometries.
*/

#include "scene/Scene.hpp"
#include "scene/query/intersect.hpp"
#include <limits>

namespace toxico {
    std::optional<SceneIntersection> Scene::intersect(const Ray3& ray, fp_type t_min, fp_type t_max) const {
        fp_type closest_t = std::numeric_limits<fp_type>::max();
        const Object* closest_object = nullptr;
        std::optional<Intersection> closest;

        // Find closest intersection
        for (const auto& object : objects) {
            const auto* geometry = geometries.resolve(object.geometry);
            if (!geometry)
                continue;

            const auto result = intersection::intersect(*geometry, object.transform, ray, t_min, t_max);
            if (result && result->t < closest_t) {
                closest_object = &object;
                closest_t = result->t;
                closest = result;
            }
        }

        // No intersection found
        if (!closest)
            return std::nullopt;

        // Intersection found
        return SceneIntersection{
            .object = *closest_object,
            .point = closest->point,
            .normal = closest->normal,
            .t = closest->t
        };
    }

    std::optional<SceneIntersection> Scene::intersect(const Ray3& ray) const {
        fp_type closest_t = std::numeric_limits<fp_type>::max();
        const Object* closest_object = nullptr;
        std::optional<Intersection> closest;

        // Find closest intersection
        for (const auto& object : objects) {
            const auto* geometry = geometries.resolve(object.geometry);
            if (!geometry)
                continue;

            const auto result = intersection::intersect(*geometry, object.transform, ray);
            if (result && result->t < closest_t) {
                closest_object = &object;
                closest_t = result->t;
                closest = result;
            }
        }

        // No intersection found
        if (!closest)
            return std::nullopt;

        // Intersection found
        return SceneIntersection{
            .object = *closest_object,
            .point = closest->point,
            .normal = closest->normal,
            .t = closest->t
        };
    }
}
