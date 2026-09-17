/*
    Object.hpp

    Declaration of a renderable object.
*/

#pragma once

#include "scene/geometry/utility/GeometryHandle.hpp"
#include "foundation/geometry/Transform.hpp"
#include "visuals/Color3.hpp"

namespace toxico {
    struct Object {
        GeometryHandle geometry;
        Transform transform;

        // @TODO: Add material system
        Color3 color = Color3(1, 1, 1);
    };
}
