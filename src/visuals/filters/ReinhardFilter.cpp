/*
    ReinhardFilter.cpp

    Implementation of a filter that applies a Reinhard operator to each pixel.
*/

#include "visuals/filters/ReinhardFilter.hpp"
#include "visuals/Color4.hpp"
#include <cstdint>

namespace toxico {
    Image ReinhardFilter::apply(const Image& image) const {
        Image result = image;
        for (auto& pixel : result) {
            // Apply a Reinhard operator to the RGB channels
            for (std::size_t i = 0; i < 3; ++i) {
                if (pixel[i] < 0)
                    pixel[i] = 0;
                else
                    pixel[i] = pixel[i] / (1.0 + pixel[i]);
            }
        }
        return result;
    }

    std::vector<Image> ReinhardFilter::apply(std::span<const Image> images) const {
        std::vector<Image> result;
        for (const auto& image : images)
            result.push_back(apply(image));
        return result;
    }
}
