/*
    SRGBToLinearFilter.hpp

    Declaration of a filter that converts the given sRGB values into their linear RGB equivalent.
*/

#pragma once

#include "visuals/filters/interfaces/IImageFilter.hpp"
#include "visuals/Image.hpp"
#include <vector>
#include <span>

namespace toxico {
    class SRGBToLinearFilter : public IImageFilter {
    public:
        /**
         * @brief Applies the filter to an image.
         * 
         * @param image The image the filter is applied to.
         * @return The modified image.
         */
        Image apply(const Image& image) const final;

        /**
         * @brief Applies the filter to a group of images simultaneously.
         * 
         * @param images The set of images the filter is applied to.
         * @return The modified images.
         */
        std::vector<Image> apply(std::span<const Image> images) const final;
    };
}
