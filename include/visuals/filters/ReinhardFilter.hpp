/*
    ReinhardFilter.hpp

    Declaration of a filter that applies a Reinhard operator to each pixel.
*/

#pragma once

#include "visuals/filters/interfaces/IImageFilter.hpp"
#include "visuals/Image.hpp"
#include <vector>
#include <span>

namespace toxico {
    class ReinhardFilter : public IImageFilter {
    public:
        /**
         * @brief Applies the filter to an image.
         * 
         * @param image The image the filter is applied to.
         */
        void apply(Image& image) const final;

        /**
         * @brief Applies the filter to a group of images simultaneously.
         * 
         * @param images The set of images the filter is applied to.
         */
        void apply(std::span<Image> images) const final;
    };
}
