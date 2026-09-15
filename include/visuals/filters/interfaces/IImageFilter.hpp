/*
    IImageFilter.hpp

    An interface for an image filter.
*/

#pragma once

#include "visuals/Image.hpp"
#include <vector>
#include <span>

namespace toxico {
    class IImageFilter {
    public:
        /**
         * @brief Applies the filter to an image.
         * 
         * @param image The image the filter is applied to.
         * @return The modified image.
         */
        virtual Image apply(const Image& image) const = 0;

        /**
         * @brief Applies the filter to a group of images simultaneously.
         * 
         * @param images The set of images the filter is applied to.
         * @return The modified images.
         */
        virtual std::vector<Image> apply(std::span<const Image> images) const = 0;

        /**
         * @brief Destructor.
         */
        virtual ~IImageFilter() = default;
    };
}
