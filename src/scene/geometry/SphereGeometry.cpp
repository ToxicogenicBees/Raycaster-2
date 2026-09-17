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

    std::optional<Intersection> SphereGeometry::intersection(const Ray3& local_ray) const {
        // Calculate coefficients of quadratic
        const Vector3 oc = local_ray.origin;
        const fp_type a = local_ray.direction.dot(local_ray.direction);
        const fp_type b = 2.0 * oc.dot(local_ray.direction);
        const fp_type c = oc.dot(oc) - 1.0;

        // Validate a solution exists
        const fp_type discriminant = b * b - 4.0 * a * c;
        if (discriminant < 0)
            return std::nullopt;

        // Solve for roots
        const fp_type sqrt_discriminant = std::sqrt(discriminant);
        const fp_type t1 = (-b - sqrt_discriminant) / (2.0 * a);
        const fp_type t2 = (-b + sqrt_discriminant) / (2.0 * a);

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
