/*
    ImageFilterSet.cpp

    Implementation of an ordered set of image filters.
*/

#include "visuals/filters/ImageFilterSet.hpp"

namespace toxico {
    void ImageFilterSet::apply(Image& image) const {
        for (auto& filter : filters_)
            filter->apply(image);
    }

    void ImageFilterSet::apply(std::span<Image> images) const {
        for(auto& filter : filters_)
            filter->apply(images);
    }
}
