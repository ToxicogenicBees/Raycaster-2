/*
    ReinhardFilter.cpp

    Implementation of a filter that applies a Reinhard operator to each pixel.
*/

#include "visuals/filters/ReinhardFilter.hpp"
#include "visuals/Color4.hpp"
#include <cstdint>

namespace toxico {
    void ReinhardFilter::apply(Image& image) const {
        for (auto& pixel : image) {
            // Apply a Reinhard operator to the RGB channels
            for (std::size_t i = 0; i < 3; ++i) {
                if (pixel[i] < 0)
                    pixel[i] = 0;
                else
                    pixel[i] = pixel[i] / (1.0 + pixel[i]);
            }
        }
    }

    void ReinhardFilter::apply(std::span<Image> images) const {
        for (auto& image : images)
            apply(image);
    }
}
