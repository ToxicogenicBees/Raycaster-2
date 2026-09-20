/*
    ImageMaterial.cpp

    Implementation of a material fetching its base color from an image.
*/

#include "rendering/material/ImageMaterial.hpp"
#include "rendering/material/utility/TextureColorSpace.hpp"
#include <algorithm>

namespace toxico {
    ImageMaterial::ImageMaterial(const std::filesystem::path& texture, const MaterialSample& sample, TextureFilterMode mode)
        : texture_(texture, TextureColorSpace::sRGB, mode),
          sample_(sample)
    {}
    
    MaterialSample ImageMaterial::sample(const Vector2& uv) const noexcept {
        auto modified_sample = sample_;
        modified_sample.base_color = texture_.sample(uv);
        return modified_sample;
    }
}
