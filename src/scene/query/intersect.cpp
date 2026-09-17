/*
    intersect.cpp

    Implementation of a free function to get the intersection of a ray with a transformed geometry.
*/

#include "scene/query/intersect.hpp"

namespace toxico::intersection {
    std::optional<Intersection> intersect(const IGeometry& geometry, const Transform& transform, const Ray3& ray, fp_type t_min, fp_type t_max) {
        // Fetch the intersection
        auto result = intersect(geometry, transform, ray);
        if (!result)
            return std::nullopt;

        // Validate world-space time constraints
        if (result->t < t_min || result->t > t_max)
            return std::nullopt;

        return result;
    }

    std::optional<Intersection> intersect(const IGeometry& geometry, const Transform& transform, const Ray3& ray) {
        // Fetch intersection in local space
        const Ray3 local_ray = transform.toLocal(ray);
        auto local_hit = geometry.intersection(local_ray);

        // No local-space intersection -> no world-space intersection
        if (!local_hit)
            return std::nullopt;

        // Fetch offset
        const Vector3 world_point = transform.toWorldPoint(local_hit->point);
        const Vector3 offset = world_point - ray.origin;

        // Convert local-space intersection to world space
        return Intersection{
            .point = world_point,
            .normal = transform.toWorldNormal(local_hit->normal),
            .t = offset.dot(ray.direction) / ray.direction.dot(ray.direction)
        };
    }
}