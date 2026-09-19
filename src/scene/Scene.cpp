/*
    Scene.cpp

    Declaration of a scene of objects, lights, and geometries.
*/

#include "scene/Scene.hpp"
#include "scene/query/GeometryInteraction.hpp"
#include "scene/query/intersect.hpp"
#include <limits>

namespace toxico {
    std::optional<SurfaceInteraction> Scene::intersect(const Ray3& ray, fp_type t_min, fp_type t_max) const {
        fp_type closest_t = std::numeric_limits<fp_type>::max();
        const Object* closest_object = nullptr;
        std::optional<GeometryInteraction> closest;

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

        // Calculate shading normal
        Vector3 shading_normal = closest->normal;
        const auto* material = materials.resolve(closest_object->material);
        if (material) {
            const auto sample = material->sample(closest->uv);
            shading_normal = (
                sample.tangent_normal.x * closest->tangent
                + sample.tangent_normal.y * closest->bitangent
                + sample.tangent_normal.z * closest->normal
            ).normal();
        }

        // Intersection found
        return SurfaceInteraction{
            .object = *closest_object,
            .point = closest->point,
            .geometric_normal = closest->normal,
            .shading_normal = shading_normal,
            .uv = closest->uv,
            .t = closest->t
        };
    }

    std::optional<SurfaceInteraction> Scene::intersect(const Ray3& ray) const {
        return intersect(ray, fp_type{0}, std::numeric_limits<fp_type>::max());
    }
}
