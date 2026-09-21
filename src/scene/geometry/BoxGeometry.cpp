/*
    BoxGeometry.cpp

    Implementation for the geometry of a box.
*/

#include "scene/geometry/BoxGeometry.hpp"
#include "scene/geometry/utility/TBNSurfaceFrame.hpp"
#include "foundation/geometry/Transform.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"
#include <cstddef>
#include <array>
#include <limits>
#include <cmath>

namespace toxico {
    const std::array<TBNSurfaceFrame, 6> faces{
        TBNSurfaceFrame{Vector3::zAxis(), Vector3::yAxis(), Vector3::xAxis()},     // +X
        TBNSurfaceFrame{-Vector3::zAxis(), Vector3::yAxis(), -Vector3::xAxis()},   // -X
        TBNSurfaceFrame{Vector3::xAxis(), -Vector3::zAxis(), Vector3::yAxis()},    // +Y
        TBNSurfaceFrame{Vector3::xAxis(), Vector3::zAxis(), -Vector3::yAxis()},    // -Y
        TBNSurfaceFrame{-Vector3::xAxis(), Vector3::yAxis(), Vector3::zAxis()},    // +Z
        TBNSurfaceFrame{Vector3::xAxis(), Vector3::yAxis(), -Vector3::zAxis()},    // -Z
    };

    BoxGeometry::BoxGeometry() {
        bounds_.expand(-Vector3::one());
        bounds_.expand(Vector3::one());
    }

    std::optional<GeometryTrace> BoxGeometry::intersection(const Ray3& local_ray) const {
        constexpr fp_type epsilon = 1e-8;
        constexpr fp_type min = -1.0;
        constexpr fp_type max =  1.0;

        fp_type t_near = -std::numeric_limits<fp_type>::infinity();
        fp_type t_far  =  std::numeric_limits<fp_type>::infinity();

        int near_axis = -1;
        int far_axis = -1;

        for (int axis = 0; axis < 3; ++axis) {
            const fp_type direction = local_ray.direction[axis];
            const fp_type origin = local_ray.origin[axis];

            // Ray is parallel to the faces in this axis
            if (std::abs(direction) < epsilon) {
                if (origin < min || origin > max)
                    return std::nullopt;
                continue;
            }

            // Get near and far axis
            fp_type axis_near = (min - origin) / direction;
            fp_type axis_far  = (max - origin) / direction;
            if (axis_near > axis_far)
                std::swap(axis_near, axis_far);

            if (axis_near > t_near) {
                t_near = axis_near;
                near_axis = axis;
            }
            if (axis_far < t_far) {
                t_far = axis_far;
                far_axis = axis;
            }
            if (t_near > t_far)
                return std::nullopt;
        }

        if (t_far < 0.0)
            return std::nullopt;

        // Get collision time and axis
        const bool inside = t_near < 0.0;
        const fp_type t = inside ? t_far : t_near;
        const int axis = inside ? far_axis : near_axis;

        // Get the sign of the colliding face
        const Vector3 point = local_ray.at(t);
        const int sign = point[axis] >= 0.0 ? 1 : -1;

        // Get the TBN surface frame for this box
        const int face = 2 * axis + (sign < 0);
        const TBNSurfaceFrame& frame = faces[face];

        // Return the intersection
        return GeometryTrace{
            .frame = frame,
            .point = point,
            .uv = Vector2{
                static_cast<fp_type>(0.5 * (frame.tangent.dot(point) + 1.0)),
                static_cast<fp_type>(0.5 * (frame.bitangent.dot(point) + 1.0))
            },
            .t = t
        };
    }

    const AABB& BoxGeometry::bounds() const {
        return bounds_;
    }
}
