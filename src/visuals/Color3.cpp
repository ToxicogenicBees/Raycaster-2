/*
    Color3.cpp

    Implementation of a simple RGBA color structure
*/

#include "visuals/Color3.hpp"
#include <stdexcept>

namespace {
    const std::array<toxico::fp_type toxico::Color3::*, toxico::Color3::channels> COLOR_CHANNELS = {
        &toxico::Color3::r, &toxico::Color3::g, &toxico::Color3::b
    };
}

namespace toxico {
    Color3::Color3(fp_type r, fp_type g, fp_type b) noexcept
        : r(r), g(g), b(b) {}

    Color3::Color3() noexcept
        : r(0.0), g(0.0), b(0.0) {}

    Color3 Color3::fromRGB8(uint8_t r, uint8_t g, uint8_t b) noexcept {
        fp_type inv255 = 1.0 / 255.0;
        return Color3{
            r * inv255,
            g * inv255,
            b * inv255
        };
    }

    std::array<uint8_t, Color3::channels> Color3::toRGB8() const noexcept {
        std::array<uint8_t, Color3::channels> result;
        for (std::size_t i = 0; i < Color3::channels; ++i)
            result[i] = static_cast<uint8_t>(this->operator[](i) * 255.0);
        return result;
    }

    fp_type Color3::operator[](std::size_t channel) const {
        return this->*COLOR_CHANNELS[channel];
    }

    fp_type& Color3::operator[](std::size_t channel) {
        return this->*COLOR_CHANNELS[channel];
    }

    fp_type Color3::at(std::size_t channel) const {
        if (channel >= Color3::channels)
            throw std::invalid_argument("Invalid color channel");

        return this->*COLOR_CHANNELS[channel];
    }

    fp_type& Color3::at(std::size_t channel) {
        if (channel >= Color3::channels)
            throw std::invalid_argument("Invalid color channel");

        return this->*COLOR_CHANNELS[channel];
    }

    Color3& Color3::operator*=(const Color3 other) noexcept {
        r *= other.r;
        g *= other.g;
        b *= other.b;
        return *this;
    }

    Color3 Color3::operator*(const Color3 other) const noexcept {
        return {
            r * other.r,
            g * other.g,
            b * other.b
        };
    }
    
    Color3& Color3::operator+=(const Color3& other) noexcept {
        r += other.r;
        g += other.g;
        b += other.b;
        return *this;
    }

    Color3 Color3::operator+(const Color3& other) const noexcept {
        return {
            r + other.r,
            g + other.g,
            b + other.b
        };
    }

    Color3& Color3::operator-=(const Color3& other) noexcept {
        r -= other.r;
        g -= other.g;
        b -= other.b;
        return *this;
    }

    Color3 Color3::operator-(const Color3& other) const noexcept {
        return {
            r - other.r,
            g - other.g,
            b - other.b
        };
    }
}
