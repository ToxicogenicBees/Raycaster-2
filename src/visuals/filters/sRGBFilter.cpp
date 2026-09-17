/*
    sRGBFilter.cpp

    Implemenetation of a filter that converts the given RBG values into their sRGB equivalent.
*/

#include "visuals/filters/sRGBFilter.hpp"
#include "visuals/Color4.hpp"
#include <cmath>

namespace {
    fp_type linearToSRGB(fp_type value) {
        if (value < 0.0031300)
            return value * 12.92;
        return 1.055 * std::pow(value, 1.0 / 2.4) - 0.055;
    }
}

namespace toxico {
    Image sRGBFilter::apply(const Image& image) const {
        Image result = image;
        for (auto& pixel : result) {
            // Modify RGB channels only
            for (std::size_t i = 0; i < 3; ++i)
                pixel[i] = linearToSRGB(pixel[i]);
        }
        return result;
    }

    std::vector<Image> sRGBFilter::apply(std::span<const Image> images) const {
        std::vector<Image> result;
        for (const auto& image : images)
            result.push_back(apply(image));
        return result;
    }
}
