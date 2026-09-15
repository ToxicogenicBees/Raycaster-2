/*
    PNGWriter.cpp

    Implementation of a .png image encoder.
*/

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "io/image/ImageWriter.hpp"
#include "io/error/FileWriteError.hpp"
#include "io/error/FileOpenError.hpp"
#include <stb_image/stb_image_write.h>
#include <unordered_set>
#include <stdexcept>
#include <cstdint>
#include <vector>

namespace {
    std::unordered_set<std::filesystem::path> SUPPORTED_FILE_TYPES {
        ".png",
        ".jpg"
    };
}

namespace toxico {
    void ImageWriter::write(const std::filesystem::path& file_name, const Image& image) const {
        // Ensure file has an extension type
        auto fixed_file_name = file_name;
        if (!fixed_file_name.has_extension())
            fixed_file_name.replace_extension(".png");

        // Validate extension
        if (!SUPPORTED_FILE_TYPES.contains(fixed_file_name.extension()))
            throw FileOpenError(fixed_file_name.string(), "Unsupported file type");

        // Format pixel data as a vector of uint8_ts
        std::vector<uint8_t> pixels;
        for (auto pixel : image) {
            for (auto channel : pixel.toRGBA8())
                pixels.push_back(channel);
        }

        // Write image
        const int channels = 4;
        int result;
        if (fixed_file_name.extension() == ".png")
            result = stbi_write_png(fixed_file_name.string().c_str(), image.size().width, image.size().height, channels, pixels.data(), image.size().width * channels);
        else if (fixed_file_name.extension() == ".jpg")
            result = stbi_write_jpg(fixed_file_name.string().c_str(), image.size().width, image.size().height, channels, pixels.data(), image.size().width * channels);

        // Validate result
        if (!result)
            throw FileWriteError(fixed_file_name.string());
    }
}
