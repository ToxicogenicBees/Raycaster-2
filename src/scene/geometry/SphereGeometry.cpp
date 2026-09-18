/*
    SphereGeometry.cpp

    Implementation for the geometry of a sphere.
*/

#include "scene/geometry/SphereGeometry.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Quadratic.hpp"
#include "foundation/math/Vector.hpp"

namespace toxico {
    SphereGeometry::SphereGeometry() noexcept
        : bounds_(-Vector3::one(), Vector3::one()) {}

    std::optional<Intersection> SphereGeometry::intersection(const Ray3& local_ray) const {
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

        // Figure out which root is correct
        fp_type t;
        if (t1 >= 0)
            t = t1;
        else if (t2 >= 0)
            t = t2;
        else
            return std::nullopt;

        // Return intersection data
        const Vector3 hit_point = local_ray.at(t);
        return Intersection{
            .point = hit_point,
            .normal = hit_point.normal(),
            .t = t
        };
    }

    const AABB& SphereGeometry::bounds() const {
        return bounds_;
    }
}
