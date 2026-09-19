/*
    GeometryInteraction.hpp

    Declaration of a struct containing info of the interaction between a geometry and a ray.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"

namespace toxico {
    struct GeometryInteraction {
        Vector3 point;
        Vector3 normal;
        Vector3 tangent;
        Vector3 bitangent;
        Vector2 uv;
        fp_type t;
    };
}
