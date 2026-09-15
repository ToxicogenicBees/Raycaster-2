/*
    ImageFilterSet.cpp

    Implementation of an ordered set of image filters.
*/

#include "visuals/filters/ImageFilterSet.hpp"

namespace toxico {
    Image ImageFilterSet::apply(const Image& image) const {
        Image result(image);
        for (auto& filter : filters_)
            result = std::move(filter->apply(result));
        return result;
    }

    std::vector<Image> ImageFilterSet::apply(std::span<const Image> images) const {
        std::vector<Image> result(images.begin(), images.end());
        for(auto& filter : filters_)
            result = std::move(filter->apply({result.begin(), result.end()}));
        return result;
    }
}
