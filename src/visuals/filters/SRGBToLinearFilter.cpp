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
    Image SRGBToLinearFilter::apply(const Image& image) const {
        Image result = image;
        for (auto& pixel : result) {
            // Modify RGB channels only
            for (std::size_t i = 0; i < 3; ++i)
                pixel[i] = srgbToLinear(pixel[i]);
        }
        return result;
    }

    std::vector<Image> SRGBToLinearFilter::apply(std::span<const Image> images) const {
        std::vector<Image> result;
        for (const auto& image : images)
            result.push_back(apply(image));
        return result;
    }
}
