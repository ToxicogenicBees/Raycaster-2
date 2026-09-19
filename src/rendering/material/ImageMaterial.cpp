/*
    ImageMaterial.cpp

    Implementation of a flat-colored material.
*/

#include "rendering/material/ImageMaterial.hpp"
#include "io/image/ImageReader.hpp"
#include <algorithm>

namespace toxico {
    ImageMaterial::ImageMaterial(const std::filesystem::path& texture, const MaterialSample& sample, Texture::FilterMode mode)
        : texture_(texture, mode),
          sample_(sample)
    {}
    
    MaterialSample ImageMaterial::sample(const Vector2& uv) const noexcept {
        auto color = texture_.sample(uv);
        return {
            .ambient = sample_.ambient * color,
            .diffuse = sample_.diffuse * color,
            .specular = sample_.specular,
            .shininess = sample_.shininess,
            .transparency = sample_.transparency,
            .reflectance = sample_.reflectance,
        };
    }
}
