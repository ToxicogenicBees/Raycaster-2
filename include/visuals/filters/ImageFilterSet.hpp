/*
    ImageFilterSet.hpp

    Declaration of an ordered set of image filters.
*/

#pragma once

#include "visuals/filters/interfaces/IImageFilter.hpp"
#include "visuals/Image.hpp"
#include <concepts>
#include <vector>
#include <memory>

namespace toxico {
    class ImageFilterSet : public IImageFilter {
    private:
        std::vector<std::unique_ptr<IImageFilter>> filters_;

    public:
        /**
         * @brief Adds a filter to the macro filter.
         * 
         * @param args The constructor arguments for the desired filter.
         */
        template<typename Filter, typename... Args>
        requires std::is_base_of_v<IImageFilter, Filter>
        void add(Args&& ...args);

        /**
         * @brief Applies the filter to an image.
         * 
         * @param image The image the filter is applied to.
         * @return The modified image.
         */
        Image apply(const Image& image) const final;

        /**
         * @brief Applies the filter to a group of images simultaneously.
         * 
         * @param images The set of images the filter is applied to.
         * @return The modified images.
         */
        std::vector<Image> apply(std::span<const Image> images) const final;
    };
}

#include "visuals/filters/ImageFilterSet.tpp"
