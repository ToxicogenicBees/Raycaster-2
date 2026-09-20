/*
    ImageMaterial.hpp

    Declaration of a material fetching its base color from an image.
*/

#pragma once

#include "rendering/material/interfaces/IMaterial.hpp"
#include "rendering/material/utility/MaterialSample.hpp"
#include "rendering/material/utility/TextureFilterMode.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"
#include "rendering/material/utility/Texture.hpp"
#include "visuals/Image.hpp"
#include <filesystem>

namespace toxico {
    class ImageMaterial final : public IMaterial {
    private:
        Texture texture_;
        MaterialSample sample_;

    public:
        /**
         * @brief Constructor.
         * 
         * @param texture The desired texture for this material.
         * @param sample A material sample used to alter the image's material properties.
         * @param mode The desired texture sampling mode (default is nearest pixel).
         */
        ImageMaterial(const std::filesystem::path& texture, const MaterialSample& sample, TextureFilterMode mode = TextureFilterMode::Nearest);
        
        /**
         * @brief Samples the albedo of the material at a UV location.
         * 
         * @param uv The UV location on the material.
         * @return Gets the albedo at the desired UV location.
         */
        MaterialSample sample(const Vector2& uv) const noexcept final;
    };
}
