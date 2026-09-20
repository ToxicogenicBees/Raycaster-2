/*
    PBRMaterial.cpp

    Implementation of a PBR material.
*/

#include "rendering/material/PBRMaterial.hpp"
#include "rendering/material/utility/TextureColorSpace.hpp"
#include <algorithm>

namespace toxico {
    PBRMaterial::PBRMaterial(const std::filesystem::path& texture, const std::filesystem::path& normal, const MaterialSample& sample, TextureFilterMode mode)
        : texture_(texture, TextureColorSpace::sRGB, mode),
          normal_(normal, TextureColorSpace::Linear, mode),
          sample_(sample)
    {}
    
    MaterialSample PBRMaterial::sample(const Vector2& uv) const noexcept {
        auto modified_sample = sample_;

        // Set base color from texture
        modified_sample.base_color = texture_.sample(uv);

        // Set tangent normal from normal map
        const auto tangent_normal_color = normal_.sample(uv);
        modified_sample.tangent_normal = Vector3(
            2.0 * tangent_normal_color.r - 1.0,
            2.0 * tangent_normal_color.g - 1.0,
            2.0 * tangent_normal_color.b - 1.0
        ).normal();

        return modified_sample;
    }
}
