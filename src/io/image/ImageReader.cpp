/*
    ImageReader.cpp

    Implementation of a .png image reader.
*/

#define STB_IMAGE_IMPLEMENTATION

#include "io/image/ImageReader.hpp"
#include "io/error/FileReadError.hpp"
#include "io/error/FileOpenError.hpp"
#include <stb_image/stb_image.h>
#include <stdexcept>
#include <cstdint>
#include <vector>

namespace toxico {
    Image ImageReader::read(const std::filesystem::path& file_name) const {
        // Ensure file has an extension type
        auto fixed_file_name = file_name;
        if (!fixed_file_name.has_extension())
            fixed_file_name.replace_extension(".png");

        // Check if the file is supported
        int channels, width, height;
        if (!stbi_info(fixed_file_name.string().c_str(), &width, &height, &channels))
            throw FileOpenError(fixed_file_name.string(), "File not found");

        // Read the image
        unsigned char* data = stbi_load(
            fixed_file_name.string().c_str(),
            &width,
            &height,
            &channels,
            4
        );

        // Throw an error if the image failed to load
        if (!data) {
            stbi_image_free(data);
            throw FileReadError(fixed_file_name.string());
        }

        // Create an image to store this data
        const auto size = Size{
            static_cast<size_t>(width),
            static_cast<size_t>(height)
        };
        Image image(size);

        // Format data into the image
        size_t i = 0;
        for (auto& pixel : image) {
            pixel = Color4::fromRGBA8(
                pixel.r = data[i],
                pixel.g = data[i + 1],
                pixel.b = data[i + 2],
                pixel.a = data[i + 3]
            );
            i += 4;
        }

        // Free stb_image memory
        stbi_image_free(data);

        // Return image
        return image;
    }
}
