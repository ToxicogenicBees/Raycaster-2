/*
    LightProperties.hpp

    Declaration of a set of properties for a light.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Quadratic.hpp"
#include "visuals/Color3.hpp"

namespace toxico {
    struct LightProperties {
        Quadratic attenuation = Quadratic(0.0, 0.0, 1.0);
        fp_type intensity = 1.0;
        Color3 color = Color3(1.0, 1.0, 1.0);
    };
}
