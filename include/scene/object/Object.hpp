/*
    Object.hpp

    Declaration of a renderable object.
*/

#pragma once

#include "scene/material/utility/MaterialHandle.hpp"
#include "scene/geometry/utility/GeometryHandle.hpp"
#include "foundation/geometry/Transform.hpp"
#include "visuals/Color3.hpp"

namespace toxico {
    struct Object {
        MaterialHandle material;
        GeometryHandle geometry;
        Transform transform;

        /**
         * @brief Constructor.
         * 
         * @param material A handle to this object's material.
         * @param geometry A handle to this object's geometry.
         */
        Object(MaterialHandle material, GeometryHandle geometry);
    };
}
