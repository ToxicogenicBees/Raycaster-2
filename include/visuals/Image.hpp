/*
    Image.hpp

    Declaration of an image object.
*/

#pragma once

#include "foundation/containers/Grid.hpp"
#include "foundation/geometry/Size.hpp"
#include "visuals/Color4.hpp"
#include <iterator>
#include <vector>
#include <span>

namespace toxico {
    class Image {
    private:
        Grid<Color4> pixels_;

    public:
        using const_iterator = Grid<Color4>::const_iterator;
        using iterator = Grid<Color4>::iterator;

        /**
         * @brief Constructor.
         *        Throws an invalid argument exeption if the pixels and size don't match.
         * 
         * @param begin The beginning of a list of pixels.
         * @param end The end of a list of pixels.
         * @param size The size of the image.
         */
        template<std::input_iterator InputIter>
        Image(InputIter begin, InputIter end, Size size);

        /**
         * @brief Constructor.
         * 
         * @param size The size of the image (default is 0x0).
         */
        Image(Size size = Size(0, 0)) noexcept;

        /**
         * @brief Gets a fully transparent image.
         * 
         * @param size The size of the image.
         * @param order The grid order for this image (default is row-major).
         */
        static Image transparent(Size size) noexcept;

        /**
         * @brief Linearly indexes a pixel.
         * 
         * @param index The linear pixel index.
         * @return The desired pixel.
         */
        const Color4& operator[](size_t index) const;
        Color4& operator[](size_t index);

        /**
         * @brief Linearly indexes a pixel.
         *        Throws an out-of-range exception if the index is invalid.
         * 
         * @param index The linear pixel index.
         * @return The desired pixel.
         */
        const Color4& at(size_t index) const;
        Color4& at(size_t index);

        /**
         * @brief Positionally indexes a pixel.
         * 
         * @param x The x-position of the pixel.
         * @param y The y-position of the pixel.
         * @return The desired pixel.
         */
        const Color4& operator()(size_t x, size_t y) const;
        Color4& operator()(size_t x, size_t y);

        /**
         * @brief Positionally indexes a pixel.
         *        Throws an out-of-range exception if the position is invalid.
         * 
         * @param x The x-position of the pixel.
         * @param y The y-position of the pixel.
         * @return The desired pixel.
         */
        const Color4& at(size_t x, size_t y) const;
        Color4& at(size_t x, size_t y);

        /**
         * @brief Gets the size of the image.
         * 
         * @return The size of the image.
         */
        Size size() const noexcept;

        /**
         * @brief Resizes the image, not preserving the layout of preexisting pixels.
         * 
         * @param size The new desired size.
         */
        void resize(Size size) noexcept;

        /**
         * @brief Fills the image with the desired color.
         * 
         * @param color The desired color.
         */
        void fill(Color4 color) noexcept;

        /**
         * @brief Gets the data of this image.
         * 
         * @return The data of this image.
         */
        std::span<const Color4> data() const noexcept;

        /**
         * @brief Gets the desired iterator for this tile's indices.
         * 
         * @return The desired iterator.
         */
        const_iterator cbegin() const noexcept;
        const_iterator begin() const noexcept;
        iterator begin() noexcept;
        const_iterator cend() const noexcept;
        const_iterator end() const noexcept;
        iterator end() noexcept;
    };
}

#include "visuals/Image.tpp"
