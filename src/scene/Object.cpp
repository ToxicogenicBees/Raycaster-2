/*
    Object.cpp

    Implementation of a renderable object.
*/

#include "scene/Object.hpp"
#include <cstddef>
#include <array>

namespace toxico {
    Object::Object(IGeometry& geometry, const Transform& transform)
        : geometry_(geometry),
          transform_(transform)
    {}

    Object::Object(IGeometry& geometry)
        : geometry_(geometry) {}

    const IGeometry& Object::geometry() const noexcept {
        return geometry_;
    }

    const Transform& Object::transform() const noexcept {
        return transform_;
    }

    Transform& Object::transform() noexcept {
        return transform_;
    }

    std::optional<Intersection> Object::intersection(const Ray3& world_ray, fp_type t_min, fp_type t_max) const {
        // Fetch intersection in local space
        const Ray3 local_ray = transform_.toLocal(world_ray);
        auto local_hit = geometry_.intersection(local_ray);

        // No local-space intersection -> no world-space intersection
        if (!local_hit)
            return std::nullopt;

        // Recalculate local-space intersection to world space
        Intersection world_hit = *local_hit;
        world_hit.point = transform_.toWorldPoint(local_hit->point);
        world_hit.normal = transform_.toWorldNormal(local_hit->normal);
        const Vector3 offset = world_hit.point - world_ray.origin;
        world_hit.t = offset.dot(world_ray.direction)
            / world_ray.direction.dot(world_ray.direction);

        // Validate world-space time constraints
        if (world_hit.t < t_min || world_hit.t > t_max)
            return std::nullopt;

        // Return the world-space intersection
        return world_hit;
    }

    AABB Object::worldBounds() const noexcept {
        // Fetch this object's geometry's local bounding box
        const auto& local_bounds = geometry_.bounds();
        
        // Fetch all 8 corners of the bounding box
        const auto min = local_bounds.lowerBound();
        const auto max = local_bounds.upperBound();
        std::array<Vector3, 8> corners;
        for (std::size_t i = 0; i < 8; ++i) {
            corners[i].x = ((i & 0x1) ? max.x : min.x);
            corners[i].y = ((i & 0x2) ? max.y : min.y);
            corners[i].z = ((i & 0x4) ? max.z : min.z);
        }

        // Create a bound around the resulting transformed corners
        AABB result;
        for (const auto& corner : corners)
            result.expand(transform().toWorldPoint(corner));
        return result;
    }
}
