/*
    SphereGeometry.cpp

    Implementation for the geometry of a sphere.
*/

#include "scene/geometry/SphereGeometry.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Quadratic.hpp"
#include "foundation/math/Vector.hpp"
#include <algorithm>
#include <numbers>

namespace toxico {
    SphereGeometry::SphereGeometry() noexcept
        : bounds_(-Vector3::one(), Vector3::one()) {}

    std::optional<GeometryInteraction> SphereGeometry::intersection(const Ray3& local_ray) const {
        // Calculate coefficients of the intersection quadratic
        const Vector3 oc = local_ray.origin;
        const fp_type a = local_ray.direction.dot(local_ray.direction);
        const fp_type b = 2.0 * oc.dot(local_ray.direction);
        const fp_type c = oc.dot(oc) - 1.0;
        const Quadratic quad(a, b, c);

        // Validate a real solution exists
        if (!quad.realRoots())
            return std::nullopt;

        // Solve for the roots
        const auto [z1, z2] = quad.roots();
        fp_type t1 = z1.real();
        fp_type t2 = z2.real();
        if (t1 > t2)
            std::swap(t1, t2);

        // Figure out which root is correct
        fp_type t;
        if (t1 >= 0)
            t = t1;
        else if (t2 >= 0)
            t = t2;
        else
            return std::nullopt;

        // Calculate UV vector
        const Vector3 hit_point = local_ray.at(t);
        const fp_type theta = std::atan2(hit_point.x, hit_point.z);
        const fp_type phi = std::asin(hit_point.y);
        const Vector2 uv = {
            static_cast<fp_type>(0.5 + theta / (2.0 * std::numbers::pi)),
            static_cast<fp_type>(0.5 + phi / std::numbers::pi)
        };

        // Calculate tangent + bitangent
        const Vector3 normal = hit_point.normal();
        const Vector3 tangent = Vector3{hit_point.z, 0, -hit_point.x}.normal();
        const Vector3 bitangent = normal.cross(tangent);

        // Return intersection data
        return GeometryInteraction{
            .point = hit_point,
            .normal = normal,
            .tangent = tangent,
            .bitangent = bitangent,
            .uv = uv,
            .t = t
        };
    }

    const AABB& SphereGeometry::bounds() const {
        return bounds_;
    }
}
