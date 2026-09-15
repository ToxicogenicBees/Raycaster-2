/*
    ClampFilter.cpp

    Implemenetation of a filter that clamps all color channels to the [0, 1] range.
*/

#include "visuals/filters/ClampFilter.hpp"
#include "visuals/Color4.hpp"
#include <cmath>

namespace toxico {
    Image ClampFilter::apply(const Image& image) const {
        Image result = image;
        for (auto& pixel : result) {
            for (std::size_t i = 0; i < pixel.channels; ++i)
                pixel[i] = std::clamp(pixel[i], fp_type{0.0}, fp_type{1.0});
        }
        return result;
    }

    std::vector<Image> ClampFilter::apply(std::span<const Image> images) const {
        std::vector<Image> result;
        for (const auto& image : images)
            result.push_back(apply(image));
        return result;
    }
}
