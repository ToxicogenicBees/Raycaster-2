/*
    Material.cpp

    Implementation of an applyable material.
*/

#include "scene/material/Material.hpp"

namespace toxico {
    Material::Material(MaterialGraphics graphics, MaterialProperties base_properties)
        : base_properties(base_properties),
          graphics(graphics)
    {}

    Material::Material(MaterialProperties base_properties)
        : base_properties(base_properties) {}
    
    MaterialProperties Material::sample(const Vector2& uv) const noexcept {
        // Copy base properties
        MaterialProperties result = base_properties;

        // Set base color from texture
        if (graphics.texture)
            result.base_color = graphics.texture->sample(uv);

        // Set tangent normal from normal map
        if (graphics.normal_map) {
            const auto tangent_normal_color = graphics.normal_map->sample(uv);
            result.tangent_normal = Vector3(
                2.0 * tangent_normal_color.r - 1.0,
                2.0 * tangent_normal_color.g - 1.0,
                2.0 * tangent_normal_color.b - 1.0
            ).normal();
        }

        return result;
    }
}
