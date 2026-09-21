/*
    TBNSurfaceFrame.cpp

    Implementation of a TBN surface frame.
*/

#include "scene/geometry/utility/TBNSurfaceFrame.hpp"

namespace toxico {
    Vector3 TBNSurfaceFrame::toWorld(const Vector3& tangent_normal) const noexcept {
        return (
            tangent * tangent_normal.x
            + bitangent * tangent_normal.y
            + normal * tangent_normal.z
        ).normal();
    }

    Vector3 TBNSurfaceFrame::toTangent(const Vector3& world_normal) const noexcept {
        return Vector3(
            tangent.dot(world_normal),
            bitangent.dot(world_normal),
            normal.dot(world_normal)
        ).normal();
    }
}