/*
    FlatMaterial.hpp

    Declaration of a flat-colored material.
*/

#pragma once

#include "rendering/material/interfaces/IMaterial.hpp"
#include "rendering/material/utility/MaterialSample.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"
#include "visuals/Color3.hpp"

namespace toxico {
    class FlatMaterial final : public IMaterial {
    private:
        MaterialSample sample_;

    public:
        /**
         * @brief Constructor.
         * 
         * @param sample The desired material sample for this material.
         */
        FlatMaterial(const MaterialSample& sample) noexcept;
        
        /**
         * @brief Samples the albedo of the material at a UV location.
         * 
         * @param uv The UV location on the material.
         * @return Gets the albedo at the desired UV location.
         */
        MaterialSample sample(const Vector2& uv) const noexcept final;
    };
}
