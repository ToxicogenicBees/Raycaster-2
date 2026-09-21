/*
    GeometryInteraction.hpp

    Declaration of a struct containing info of the interaction between a geometry and a ray.
*/

#pragma once

#include "scene/geometry/utility/TBNSurfaceFrame.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"

namespace toxico {
    struct GeometryInteraction {
        TBNSurfaceFrame frame;
        Vector3 point;
        Vector2 uv;
        fp_type t;
    };
}
