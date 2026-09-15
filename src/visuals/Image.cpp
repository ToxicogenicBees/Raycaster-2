/*
    Image.cpp

    Implementation of an image object.
*/

#include "visuals/Image.hpp"
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <vector>
#include <cmath>

namespace toxico {
    Image::Image(Size size, GridOrder order) noexcept
        : pixels_(size, order) {}

    Image Image::transparent(Size size, GridOrder order) noexcept {
        Image image(size, order);
        image.fill(Color4::transparent());
        return image;
    }

    const Color4& Image::operator[](size_t index) const {
        return pixels_[index];
    }

    Color4& Image::operator[](size_t index) {
        return pixels_[index];
    }

    const Color4& Image::at(size_t index) const {
        return pixels_.at(index);
    }

    Color4& Image::at(size_t index) {
        return pixels_.at(index);
    }

    const Color4& Image::operator()(size_t x, size_t y) const {
        return pixels_(x, y);
    }

    Color4& Image::operator()(size_t x, size_t y) {
        return pixels_(x, y);
    }

    const Color4& Image::at(size_t x, size_t y) const {
        return pixels_.at(x, y);
    }

    Color4& Image::at(size_t x, size_t y) {
        return pixels_.at(x, y);
    }

    Size Image::size() const noexcept {
        return pixels_.size();
    }

    void Image::resize(Size size) noexcept {
        pixels_.resize(size);
    }

    void Image::fill(Color4 color) noexcept {
        pixels_.fill(color);
    }

    GridOrder Image::order() const noexcept {
        return pixels_.order();
    }

    std::span<const Color4> Image::data() const noexcept {
        return {begin(), end()};
    }
    
    Image::const_iterator Image::cbegin() const noexcept {
        return pixels_.cbegin();
    }
    
    Image::const_iterator Image::begin() const noexcept {
        return pixels_.begin();
    }

    Image::iterator Image::begin() noexcept {
        return pixels_.begin();
    }
    
    Image::const_iterator Image::cend() const noexcept {
        return pixels_.cend();
    }
    
    Image::const_iterator Image::end() const noexcept {
        return pixels_.end();
    }
    
    Image::iterator Image::end() noexcept {
        return pixels_.end();
    }
}
