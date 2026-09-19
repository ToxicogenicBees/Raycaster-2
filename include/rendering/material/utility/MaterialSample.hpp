/*
    MaterialSample.hpp

    Declaration of a struct containing sampled material values.
*/

#pragma once

#include "foundation/math/Vector.hpp"
#include "visuals/Color3.hpp"

namespace toxico {
    struct MaterialSample {
        Vector3 tangent_normal = Vector3::zAxis();
        Color3 ambient = Color3(0.0, 0.0, 0.0);
        Color3 diffuse = Color3(0.0, 0.0, 0.0);
        Color3 specular = Color3(0.0, 0.0, 0.0);
        fp_type shininess = 0.0;
        fp_type transparency = 0.0;
        fp_type reflectance = 0.0;
    };
}
