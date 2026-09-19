/*
    ImageMaterial.cpp

    Implementation of a flat-colored material.
*/

#include "rendering/material/ImageMaterial.hpp"
#include "visuals/filters/SRGBToLinearFilter.hpp"
#include "io/image/ImageReader.hpp"
#include <algorithm>

namespace toxico {
    ImageMaterial::ImageMaterial(const std::filesystem::path& texture, const MaterialSample& sample)
        : sample_(sample)
    {
        // Load texture
        ImageReader reader;
        auto srgb_image = reader.read(texture);

        // Convert to linear color
        SRGBToLinearFilter filter;
        texture_ = filter.apply(srgb_image);
    }
    
    MaterialSample ImageMaterial::sample(const Vector2& uv) const noexcept {
        const auto u = uv.x - std::floor(uv.x);
        const auto v = fp_type{1.0} - (uv.y - std::floor(uv.y));

        const auto width = static_cast<fp_type>(texture_.size().width);
        const auto height = static_cast<fp_type>(texture_.size().height);

        const auto row = static_cast<std::size_t>(std::clamp(v, fp_type{0}, fp_type{1}) * (height - 1));
        const auto col = static_cast<std::size_t>(std::clamp(u, fp_type{0}, fp_type{1}) * (width - 1));

        Color3 color = {
            texture_.at(row, col).r,
            texture_.at(row, col).g,
            texture_.at(row, col).b
        };

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
