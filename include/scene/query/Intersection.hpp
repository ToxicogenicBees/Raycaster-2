/*
    Intersection.hpp

    Declaration of a struct containing info of the intersection between an object and a ray in world space.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"

namespace toxico {
    struct Intersection {
        Vector3 point;
        Vector3 normal;
        fp_type t;
    };
}
