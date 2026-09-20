/*
    Texture.hpp

    Declaration of an image-based texture.
*/

#pragma once

#include "rendering/material/utility/TextureColorSpace.hpp"
#include "rendering/material/utility/TextureFilterMode.hpp"
#include "foundation/math/Vector.hpp"
#include "visuals/Color3.hpp"
#include "visuals/Image.hpp"
#include <filesystem>

namespace toxico {
    class Texture {
    public:
        /**
         * @brief Constructor.
         * 
         * @param image The desired image for this texture.
         * @param space The color space of the provided image.
         * @param mode The filtering mode for this texture.
         */
        Texture(const std::filesystem::path& image, TextureColorSpace space, TextureFilterMode mode = TextureFilterMode::Nearest);
        Texture(const Image& image, TextureColorSpace space, TextureFilterMode mode = TextureFilterMode::Nearest);

        /**
         * @brief Creates a magenta and black checkered texture.
         * 
         * @return A magenta and black textured texture.
         */
        static Texture missing();

        /**
         * @brief Samples this texture at the desired UV position.
         * 
         * @param uv The desired UV position.
         * @return The color at this position.
         */
        Color3 sample(const Vector2& uv) const noexcept;

        /**
         * @brief Gets the raw image stored in this texture.
         * 
         * @return The raw image stored in this texture.
         */
        const Image& image() const noexcept;

    private:
        Image image_;
        TextureFilterMode mode_;

        // Samples by choosing the nearest pixel
        Color3 sampleNearest_(const Vector2& uv) const noexcept;

        // Samples by interpolating between near pixel
        Color3 sampleBilinear_(const Vector2& uv) const noexcept;
    };
}
