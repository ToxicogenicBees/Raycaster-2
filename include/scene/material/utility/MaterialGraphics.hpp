/*
    MaterialGraphics.hpp

    Declaration of a struct containing graphics for a material.
*/

#pragma once

#include "rendering/texture/Texture.hpp"
#include <optional>

namespace toxico {
    struct MaterialGraphics {
        std::optional<Texture> texture;
        std::optional<Texture> normal_map;
    };
}
