/*
    PlaneGeometry.cpp

    Implementation for the geometry of a plane.
*/

#include "scene/geometry/PlaneGeometry.hpp"
#include "foundation/geometry/Transform.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"
#include <limits>
#include <cmath>

namespace toxico {
    std::optional<GeometryInteraction> PlaneGeometry::intersection(const Ray3& local_ray) const {
        // https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html#SECTION00023500000000000000
    
        Transform transform;
        const Vector3 normal = Transform::local_up;
        const Vector3 tangent = Transform::local_right;         // +U
        const Vector3 bitangent = Transform::local_forward;     // +V
        const fp_type n_dot_v = normal.dot(local_ray.direction);

        // Ray is parallel to the plane if n_dot_v is 0. Return invalid intersection.
        if (std::fabs(n_dot_v) < std::numeric_limits<fp_type>::epsilon())
            return std::nullopt;

        // Find time of intersection
        fp_type t = -normal.dot(local_ray.origin) / n_dot_v;
        if (t < 0)
            return std::nullopt;

        // Return the intersection
        const auto point = local_ray.at(t);
        return GeometryInteraction{
            .point = local_ray.at(t),
            .normal = normal,
            .tangent = tangent,
            .bitangent = bitangent,
            .uv = Vector2(point.x, -point.z),
            .t = t,
        };
    }

    const AABB& PlaneGeometry::bounds() const {
        return bounds_;
    }
}
