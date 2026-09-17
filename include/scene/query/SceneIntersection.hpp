/*
    SceneIntersection.hpp

    Declaration of a struct containing info of the intersection between an object and a ray in a scene.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"
#include "scene/object/Object.hpp"

namespace toxico {
    struct SceneIntersection {
        const Object& object;
        Vector3 point;
        Vector3 normal;
        fp_type t;
    };
}
