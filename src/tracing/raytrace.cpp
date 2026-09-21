/*
    raytrace.cpp

    Declaration of a free function to trace a ray through a scene.
*/

#include "tracing/raytrace.hpp"
#include "foundation/math/Vector.hpp"
#include <limits>

namespace toxico::raytrace {
    std::optional<GeometryTrace> worldIntersection(const IGeometry& geometry, const Transform& transform, const Ray3& ray, fp_type t_min, fp_type t_max) {
        // Fetch intersection in local space
        const Ray3 local_ray = transform.toLocal(ray);
        auto local_hit = geometry.intersection(local_ray);

        // No local-space intersection -> no world-space intersection
        if (!local_hit)
            return std::nullopt;

        // Validate time constraints
        const Vector3 world_point = transform.toWorldPoint(local_hit->point);
        const Vector3 offset = world_point - ray.origin;
        const fp_type t = offset.dot(ray.direction) / ray.direction.dot(ray.direction);
        if (t < t_min || t > t_max)
            return std::nullopt;

        // Convert local-space intersection to world space
        return GeometryTrace{
            .frame{
                .tangent = transform.toWorldVector(local_hit->frame.tangent).normal(),
                .bitangent = transform.toWorldVector(local_hit->frame.bitangent).normal(),
                .normal = transform.toWorldNormal(local_hit->frame.normal).normal(),
            },
            .point = world_point,
            .uv = local_hit->uv,
            .t = t
        };
    }

    std::optional<GeometryTrace> worldIntersection(const IGeometry& geometry, const Transform& transform, const Ray3& ray) {
        return worldIntersection(geometry, transform, ray, fp_type{0.0}, std::numeric_limits<fp_type>::max());
    }

    std::optional<SceneTrace> trace(const Ray3& ray, const Scene& scene, fp_type t_min, fp_type t_max) {
        // Find the closest intersection between the ray and an object in the scene
        fp_type closest_t = std::numeric_limits<fp_type>::max();
        const Object* closest_object = nullptr;
        std::optional<GeometryTrace> closest;
        for (const auto& object : scene.objects) {
            const auto* geometry = scene.geometries.resolve(object.geometry);
            if (!geometry)
                continue;

            const auto result = raytrace::worldIntersection(*geometry, object.transform, ray, t_min, t_max);
            if (result && result->t < closest_t) {
                closest_object = &object;
                closest_t = result->t;
                closest = result;
            }
        }

        // No intersection found
        if (!closest)
            return std::nullopt;

        // Get if this ray intersects a front face
        const auto geometric_normal = closest->frame.normal;
        const bool front_face = ray.direction.dot(geometric_normal) < 0.0;

        // Calculate shading normal
        Vector3 shading_normal = geometric_normal;
        if (const auto* material = scene.materials.resolve(closest_object->material)) {
            const auto sample = material->sample(closest->uv);
            shading_normal = closest->frame.toWorld(sample.tangent_normal).normal();
        }
        if (!front_face)
            shading_normal = -shading_normal;

        // Intersection found
        return SceneTrace{
            .object = *closest_object,
            .point = closest->point,
            .geometric_normal = geometric_normal,
            .shading_normal = shading_normal,
            .uv = closest->uv,
            .t = closest->t,
            .front_face = front_face
        };
    }
    
    std::optional<SceneTrace> trace(const Ray3& ray, const Scene& scene) {
        return trace(ray, scene, fp_type{0.0}, std::numeric_limits<fp_type>::max());
    }
}