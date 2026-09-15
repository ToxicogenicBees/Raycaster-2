/*
    Color4.cpp

    Implementation of a simple RGBA color structure
*/

#include "visuals/Color4.hpp"
#include <stdexcept>

namespace {
    const std::array<toxico::fp_type toxico::Color4::*, toxico::Color4::channels> COLOR_CHANNELS = {
        &toxico::Color4::r, &toxico::Color4::g, &toxico::Color4::b, &toxico::Color4::a
    };
}

namespace toxico {
    Color4::Color4(fp_type r, fp_type g, fp_type b, fp_type a) noexcept
        : r(r), g(g), b(b), a(a) {}

    Color4::Color4() noexcept
        : r(0.0), g(0.0), b(0.0), a(0.0) {}

    Color4 Color4::transparent() noexcept {
        return Color4();
    }

    Color4 Color4::fromRGBA8(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept {
        fp_type inv255 = 1.0 / 255.0;
        return Color4{
            r * inv255,
            g * inv255,
            b * inv255,
            a * inv255
        };
    }

    std::array<uint8_t, Color4::channels> Color4::toRGBA8() const noexcept {
        std::array<uint8_t, Color4::channels> result;
        for (std::size_t i = 0; i < Color4::channels; ++i)
            result[i] = static_cast<uint8_t>(this->operator[](i) * 255.0);
        return result;
    }

    fp_type Color4::operator[](std::size_t channel) const {
        return this->*COLOR_CHANNELS[channel];
    }

    fp_type& Color4::operator[](std::size_t channel) {
        return this->*COLOR_CHANNELS[channel];
    }

    fp_type Color4::at(std::size_t channel) const {
        if (channel >= Color4::channels)
            throw std::invalid_argument("Invalid color channel");

        return this->*COLOR_CHANNELS[channel];
    }

    fp_type& Color4::at(std::size_t channel) {
        if (channel >= Color4::channels)
            throw std::invalid_argument("Invalid color channel");

        return this->*COLOR_CHANNELS[channel];
    }
}
