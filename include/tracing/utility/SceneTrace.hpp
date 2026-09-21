/*
    SceneTrace.hpp

    Declaration of a struct containing info of the intersection between an object and a ray in a scene.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"
#include "scene/object/Object.hpp"

namespace toxico {
    struct SceneTrace {
        const Object& object;
        Vector3 point;
        Vector3 geometric_normal;
        Vector3 shading_normal;
        Vector2 uv;
        fp_type t;
        bool front_face;
    };
}
