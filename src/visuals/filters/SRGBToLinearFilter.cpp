/*
    SRGBToLinearFilter.cpp

    Implemenetation of a filter that converts the given sRBG values into their linear RGB equivalent.
*/

#include "visuals/filters/SRGBToLinearFilter.hpp"
#include "visuals/Color4.hpp"
#include <cmath>

namespace {
    fp_type srgbToLinear(fp_type value) {
        if (value < 0.04045)
            return value / 12.92;
        return std::pow((value + 0.055) / 1.055, 2.4);
    }
}

namespace toxico {
    void SRGBToLinearFilter::apply(Image& image) const {
        for (auto& pixel : image) {
            // Modify RGB channels only
            for (std::size_t i = 0; i < 3; ++i)
                pixel[i] = srgbToLinear(pixel[i]);
        }
    }

    void SRGBToLinearFilter::apply(std::span<Image> images) const {
        for (auto& image : images)
            apply(image);
    }
}
