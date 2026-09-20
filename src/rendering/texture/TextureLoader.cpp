/*
    TextureLoader.cpp

    Implementation of a texture loader.
*/

#include "rendering/texture/TextureLoader.hpp"
#include "rendering/texture/utility/TextureColorSpace.hpp"
#include "io/image/ImageReader.hpp"

namespace toxico {
    std::optional<Texture> TextureLoader::load(const std::filesystem::path& texture, TextureType type, TextureFilterMode mode) const {
        try {
            ImageReader reader;
            const auto image = reader.read(texture);

            switch(type) {
            case (TextureType::NormalMap):
                return Texture(image, TextureColorSpace::Linear, mode);
            case (TextureType::Graphics):
                return Texture(image, TextureColorSpace::sRGB, mode);
            default:
                return Texture(image, TextureColorSpace::sRGB, mode);
            }
        }
        catch(...) {
            return std::nullopt;
        }
    }

    Texture TextureLoader::tryLoad(const std::filesystem::path& texture, TextureType type, TextureFilterMode mode) const {
        auto result = load(texture, type, mode);
        if (result)
            return *result;
        return placeholder(type);
    }

    Texture TextureLoader::placeholder(TextureType type) const {
        switch(type) {
        case (TextureType::NormalMap):
            return Texture::flat(Color3(0.5, 0.5, 1));
        case (TextureType::Graphics):
            return Texture::missing();
        default:
            return Texture::missing();
        }
    }
}
