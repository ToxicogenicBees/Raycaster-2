/*
    TextureLoader.hpp

    Declaration of a texture loader.
*/

#pragma once

#include "rendering/texture/utility/TextureFilterMode.hpp"
#include "rendering/texture/utility/TextureType.hpp"
#include "rendering/texture/Texture.hpp"
#include <filesystem>
#include <optional>

namespace toxico {
    class TextureLoader {
    public:
        /**
         * @brief Loads a texture from a file.
         * 
         * @param texture The file this texture is stored in.
         * @param type The type of texture stored in this file.
         * @param mode The desired filtering mode for this texture.
         * @return The loaded texture, or std::nullopt if the file couldn't be loaded.
         */
        std::optional<Texture> load(const std::filesystem::path& texture, TextureType type, TextureFilterMode mode) const;

        /**
         * @brief Loads a texture from a file, or a placeholder if the file couldn't be loaded.
         * 
         * @param texture The file this texture is stored in.
         * @param type The type of texture stored in this file.
         * @param mode The desired filtering mode for this texture.
         * @return The loaded texture, or a placeholder if the file couldn't be loaded.
         */
        Texture tryLoad(const std::filesystem::path& texture, TextureType type, TextureFilterMode mode) const;

        /**
         * @brief Creates a placeholder texture for the desired texture type.
         * 
         * @param type The desired texture type.
         * @return An appropriate placeholder texture.
         */
        Texture placeholder(TextureType type) const;
    };
}
