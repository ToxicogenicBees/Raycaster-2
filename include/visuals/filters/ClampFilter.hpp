/*
    ClampFilter.hpp

    Declaration of a filter that clamps all color channels to the [0, 1] range.
*/

#pragma once

#include "visuals/filters/interfaces/IImageFilter.hpp"
#include "visuals/Image.hpp"
#include <vector>
#include <span>

namespace toxico {
    class ClampFilter : public IImageFilter {
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
