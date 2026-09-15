/*
    ImageReader.hpp

    Declaration of an image reader.
*/

#pragma once

#include "visuals/Image.hpp"
#include <filesystem>

namespace toxico {
    class ImageReader {
    public:
        /**
         * @brief Reads an image from a file.
         * 
         * @param file_name The name of the image file.
         * @return The read image.
         */
        Image read(const std::filesystem::path& file_name) const;
    };
}
