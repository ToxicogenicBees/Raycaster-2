/*
    AmbientLight.hpp

    Declaration of an ambient light source.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include "visuals/Color3.hpp"

namespace toxico {
    struct AmbientLight {
        Color3 color;
        fp_type intensity;
    };
}
