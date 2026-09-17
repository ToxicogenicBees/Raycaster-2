/*
    LightAttenuation.hpp

    Declaration of a light attenuation functor.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"

namespace toxico {
    struct LightAttenuation {
        fp_type constant = 1.0;
        fp_type linear = 0.0;
        fp_type quadratic = 0.0;

        /**
         * @brief Calculates the attenuation of light for the given distance.
         * 
         * @param distance The distance being attenuated over.
         * @return The resulting intensity multiplier at this distance.
         */
        fp_type operator()(fp_type distance) const noexcept;
    };
}
