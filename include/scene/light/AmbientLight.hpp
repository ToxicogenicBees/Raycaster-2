/*
    AmbientLight.hpp

    Declaration of an ambient light source.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include "visuals/Color3.hpp"

namespace toxico {
    struct AmbientLight {
        Color3 color = Color3(1.0, 1.0, 1.0);
        fp_type intensity = 0.0;
    };
}
