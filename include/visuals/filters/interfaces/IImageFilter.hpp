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
         */
        virtual void apply(Image& image) const = 0;

        /**
         * @brief Applies the filter to a group of images simultaneously.
         * 
         * @param images The set of images the filter is applied to.
         */
        virtual void apply(std::span<Image> images) const = 0;

        /**
         * @brief Destructor.
         */
        virtual ~IImageFilter() = default;
    };
}
