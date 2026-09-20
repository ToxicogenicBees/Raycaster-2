/*
    Texture.hpp

    Declaration of an image-based texture.
*/

#include "rendering/texture/Texture.hpp"
#include "visuals/filters/SRGBToLinearFilter.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/geometry/Size.hpp"
#include "visuals/Color4.hpp"
#include <iostream>
#include <cstddef>
#include <cmath>

namespace {
    fp_type wrap_uv(fp_type value) {
        return value - std::floor(value);
    }

    std::size_t wrap_index(std::ptrdiff_t index, std::size_t size) {
        const auto n = static_cast<std::ptrdiff_t>(size);
        return static_cast<std::size_t>((index % n + n) % n);
    }
}

namespace toxico {
    Texture Texture::missing() {
        const Size size{16, 16};
        Image result(size);

        for (std::size_t i = 0; i < size.height; ++i) {
            for (std::size_t j = 0; j < size.width; ++j) {
                if ((i & 1) != (j & 1))
                    result.at(i, j) = Color4(1, 0, 1, 1);
                else
                    result.at(i, j) = Color4(0, 0, 0, 1);
            }
        }

        return Texture(result, TextureColorSpace::Linear, TextureFilterMode::Nearest);
    }

    Texture Texture::flat(const Color3& color) {
        // Create an image holding this color
        Image image(Size{1, 1});
        image.at(0, 0) = Color4(color, 1.0);

        // Create a texture with this image
        return Texture(image, TextureColorSpace::Linear, TextureFilterMode::Nearest);
    }

    Texture::Texture(const Image& image, TextureColorSpace space, TextureFilterMode mode)
        : mode_(mode)
    {
        if (space == TextureColorSpace::sRGB) {
            SRGBToLinearFilter filter;
            image_ = filter.apply(image);
        }
        else {
            image_ = image;
        }
    }

    Texture::Texture() {
        *this = Texture::flat(Color3(0, 0, 0));
    }

    Color3 Texture::sample(const Vector2& uv) const noexcept {
        switch(mode_) {
        case (TextureFilterMode::Bilinear):
            return sampleBilinear_(uv);
        case (TextureFilterMode::Nearest):
            return sampleNearest_(uv);
        default:
            return sampleNearest_(uv);
        }
    }

    Color3 Texture::sampleNearest_(const Vector2& uv) const noexcept {
        // Fetch the sub-pixel this UV position maps to
        const auto u = wrap_uv(uv.x);
        const auto v = 1.0 - wrap_uv(uv.y);
        const fp_type x = u * image_.size().width - 0.5;
        const fp_type y = v * image_.size().height - 0.5;

        // Fetch the pixel this sub-pixel is closest to
        const auto col = wrap_index(static_cast<std::ptrdiff_t>(std::round(x)), image_.size().width);
        const auto row = wrap_index(static_cast<std::ptrdiff_t>(std::round(y)), image_.size().height);
        const auto& pixel = image_.at(row, col);
        return pixel.getRGB();
    }

    Color3 Texture::sampleBilinear_(const Vector2& uv) const noexcept {
        // Fetch the sub-pixel this UV position maps to
        const auto u = wrap_uv(uv.x);
        const auto v = 1.0 - wrap_uv(uv.y);
        const fp_type x = u * image_.size().width - 0.5;
        const fp_type y = v * image_.size().height - 0.5;

        // Fetch the pixel bounds around this sub-pixel
        const auto x_floor = std::floor(x);
        const auto y_floor = std::floor(y);
        const auto x0 = wrap_index(static_cast<std::ptrdiff_t>(x_floor), image_.size().width);
        const auto x1 = wrap_index(static_cast<std::ptrdiff_t>(x_floor) + 1, image_.size().width);
        const auto y0 = wrap_index(static_cast<std::ptrdiff_t>(y_floor), image_.size().height);
        const auto y1 = wrap_index(static_cast<std::ptrdiff_t>(y_floor) + 1, image_.size().height);

        const fp_type tx = x - x_floor;
        const fp_type ty = y - y_floor;

        // Fetch the four pixels between this sub-pixel
        const auto get_pixel = [this](std::size_t row, std::size_t col) {
            const auto& pixel = image_.at(row, col);
            return pixel.getRGB();
        };
        const Color3 c00 = get_pixel(y0, x0);
        const Color3 c10 = get_pixel(y0, x1);
        const Color3 c01 = get_pixel(y1, x0);
        const Color3 c11 = get_pixel(y1, x1);

        // Interpolate the pixels
        return
            c00 * ((1.0 - tx) * (1.0 - ty)) +
            c10 * (tx * (1.0 - ty)) +
            c01 * ((1.0 - tx) * ty) +
            c11 * (tx * ty);
    }

    const Image& Texture::image() const noexcept {
        return image_;
    }
}
