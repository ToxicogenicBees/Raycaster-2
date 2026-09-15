/*
    ImageWriter.hpp

    Declaration of an image writer.
*/

#pragma once

#include "visuals/Image.hpp"
#include <filesystem>

namespace toxico {
    class ImageWriter {
    public:
        /**
         * @brief Encodes an image to a file.
         * 
         * @param file_name The name of the image file.
         * @param image The image being encoded.
         */
        void write(const std::filesystem::path& file_name, const Image& image) const;
    };
}
