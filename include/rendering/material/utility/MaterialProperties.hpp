/*
    MaterialProperties.hpp

    Declaration of a struct containing material property values.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"
#include "visuals/Color3.hpp"

namespace toxico {
    struct MaterialProperties {
        Vector3 tangent_normal = Vector3::zAxis();
        Color3 base_color = Color3(1, 1, 1);
        Color3 emission = Color3(0, 0, 0);
        fp_type metallic = 0.0;
        fp_type roughness = 0.0;
        fp_type transmission = 0.0;
        fp_type ior = 1.0;
    };
}
