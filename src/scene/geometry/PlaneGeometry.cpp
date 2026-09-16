/*
    PlaneGeometry.cpp

    Implementation for the geometry of a plane.
*/

#include "scene/geometry/PlaneGeometry.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"
#include <limits>
#include <cmath>

namespace toxico {
    std::optional<LocalIntersection> PlaneGeometry::intersection(const Ray3& local_ray) const {
        // https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html#SECTION00023500000000000000
    
        const Vector3 normal = Vector3::yAxis();
        const fp_type n_dot_v = normal.dot(local_ray.direction);

        // Ray is parallel to the plane if n_dot_v is 0. Return invalid intersection.
        if (std::fabs(n_dot_v) < std::numeric_limits<fp_type>::epsilon())
            return std::nullopt;

        // Find time of intersection
        fp_type t = -normal.dot(local_ray.origin) / n_dot_v;
        if (t < 0)
            return std::nullopt;

        // Return the intersection
        return LocalIntersection{
            .point = local_ray.at(t),
            .normal = (n_dot_v > 0 ? -normal : normal),
            .t = t
        };
    }

    const AABB& PlaneGeometry::bounds() const {
        return bounds_;
    }
}
