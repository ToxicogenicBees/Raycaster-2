/*
    Material.hpp

    Declaration of an applyable material.
*/

#pragma once

#include "scene/material/utility/MaterialProperties.hpp"
#include "scene/material/utility/MaterialGraphics.hpp"
#include "foundation/math/Vector.hpp"

namespace toxico {
    struct Material {
        MaterialProperties base_properties;
        MaterialGraphics graphics;

        /**
         * @brief Constructor.
         * 
         * @param graphics The desired graphics for this material.
         * @param base_properties The base properties of this material.
         */
        Material(MaterialGraphics graphics, MaterialProperties base_properties = MaterialProperties{});

        /**
         * @brief Constructor.
         * 
         * @param base_properties The base properties of this material.
         */
        Material(MaterialProperties base_properties = MaterialProperties{});

        /**
         * @brief Fetches the properties of the material at a UV location.
         * 
         * @param uv The UV location on the material.
         * @return Gets the material properties at the desired UV location.
         */
        MaterialProperties sample(const Vector2& uv) const noexcept;
    };
}
