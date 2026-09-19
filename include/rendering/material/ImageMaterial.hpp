/*
    ImageMaterial.hpp

    Declaration of a flat-colored material.
*/

#pragma once

#include "rendering/material/interfaces/IMaterial.hpp"
#include "rendering/material/utility/MaterialSample.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"
#include "visuals/Image.hpp"
#include <filesystem>

namespace toxico {
    class ImageMaterial final : public IMaterial {
    private:
        Image texture_;
        MaterialSample sample_;

    public:
        /**
         * @brief Constructor.
         * 
         * @param texture The desired texture for this material.
         */
        ImageMaterial(const std::filesystem::path& texture, const MaterialSample& sample);
        
        /**
         * @brief Samples the albedo of the material at a UV location.
         * 
         * @param uv The UV location on the material.
         * @return Gets the albedo at the desired UV location.
         */
        MaterialSample sample(const Vector2& uv) const noexcept final;
    };
}
