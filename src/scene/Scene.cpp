/*
    Scene.cpp

    Declaration of a scene of objects, lights, and geometries.
*/

#include "scene/Scene.hpp"
#include "scene/query/intersect.hpp"
#include <limits>

namespace toxico {
    GeometryHandle Scene::getPrimitive(GeometryPrimitives type) {
        return geometries_.getPrimitive(type);
    }

    Object& Scene::createObject(GeometryPrimitives geometry) {
        auto handle = geometries_.getPrimitive(geometry);
        objects_.push_back({
            .geometry = handle
        });
        return objects_.back();
    }

    Object& Scene::createObject(GeometryHandle geometry) {
        objects_.push_back({
            .geometry = geometry
        });
        return objects_.back();
    }

    std::optional<SceneIntersection> Scene::intersect(const Ray3& ray, fp_type t_min, fp_type t_max) const {
        fp_type closest_t = std::numeric_limits<fp_type>::max();
        const Object* closest_object = nullptr;
        std::optional<Intersection> closest;

        // Find closest intersection
        for (const auto& object : objects_) {
            const auto* geometry = geometries_.resolve(object.geometry);
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
        for (const auto& object : objects_) {
            const auto* geometry = geometries_.resolve(object.geometry);
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
