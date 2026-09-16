/*
    SphereGeometry.cpp

    Implementation for the geometry of a sphere.
*/

#include "scene/geometry/SphereGeometry.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"

namespace toxico {
    SphereGeometry::SphereGeometry() noexcept
        : bounds_(-Vector3::one(), Vector3::one()) {}

    std::optional<LocalIntersection> SphereGeometry::intersection(const Ray3& local_ray) const {
        // https://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html

        // Ensure there is a possible intersection within the sphere
        const Vector3 L = -local_ray.origin;
        const fp_type tc = L.dot(local_ray.direction);
        const fp_type radius_squared = 1.0;
        const fp_type distance_squared = L.dot(L) - tc * tc;
        if (distance_squared > radius_squared)
            return std::nullopt;

        // Find the two possible "times" of collision
        const fp_type offset = std::sqrt(radius_squared - distance_squared);
        const fp_type t1 = tc - offset;
        const fp_type t2 = tc + offset;

        // Determine the appropriate time of collision, if one exists
        if (t1 < 0 && t2 < 0)
            return std::nullopt;
        const auto t = (t1 < t2 ? t1 : t2);

        // Return the intersection
        auto hit_point = local_ray.at(t);
        return LocalIntersection{
            .point = hit_point,
            .normal = hit_point.normal(),
            .t = t
        };
    }

    const AABB& SphereGeometry::bounds() const {
        return bounds_;
    }
}
