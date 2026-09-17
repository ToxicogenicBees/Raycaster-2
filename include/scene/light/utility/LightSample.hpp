/*
    LightSample.hpp

    Declaration of a struct containing sampled light data.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"
#include "visuals/Color3.hpp"

namespace toxico {
    struct LightSample {
        Vector3 direction;
        Color3 color;
        fp_type distance;
    };
}
