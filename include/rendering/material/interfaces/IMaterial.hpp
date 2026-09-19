/*
    IMaterial.hpp

    An interface for a material.
*/

#pragma once

#include "rendering/material/utility/MaterialSample.hpp"
#include "foundation/math/Vector.hpp"

namespace toxico {
    class IMaterial {
    public:
        /**
         * @brief Samples the albedo of the material at a UV location.
         * 
         * @param uv The UV location on the material.
         * @return Gets the albedo at the desired UV location.
         */
        virtual MaterialSample sample(const Vector2& uv) const noexcept = 0;

        /**
         * @brief Destructor.
         */
        virtual ~IMaterial() = default;
    };
}
