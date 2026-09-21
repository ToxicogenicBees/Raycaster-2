/*
    TBNSurfaceFrame.hpp

    Declaration of a TBN surface frame.
*/

#pragma once

#include "foundation/math/Vector.hpp"

namespace toxico {
    struct TBNSurfaceFrame {
        Vector3 tangent;
        Vector3 bitangent;
        Vector3 normal;

        /**
         * @brief Transforms a normalized tangent-space normal into world space.
         *
         * @param tangent_normal A normalized normal in tangent-space coordinates.
         * @return The resulting normalized world-space normal.
         */
        Vector3 toWorld(const Vector3& tangent_normal) const noexcept;

        /**
         * @brief Transforms a normalized world-space normal into tangent space.
         *
         * @param world_normal A normalized normal in world-space coordinates.
         * @return The resulting normalized tangent-space normal.
         */
        Vector3 toTangent(const Vector3& world_normal) const noexcept;
    };
}