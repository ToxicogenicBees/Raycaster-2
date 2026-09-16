/*
    Object.hpp

    Declaration of a renderable object.
*/

#pragma once

#include "scene/geometry/GeometryHandle.hpp"
#include "foundation/geometry/Transform.hpp"

namespace toxico {
    struct Object {
        GeometryHandle geometry;
        Transform transform;
    };
}
