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
        // Direction from the light to the surface
        Vector3 direction;

        // Attenuated light contribution at this point
        Color3 color;

        // The distance the light traveled to reach this point
        fp_type distance;
    };
}
