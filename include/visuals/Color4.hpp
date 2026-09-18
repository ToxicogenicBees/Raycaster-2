/*
    Color4.hpp

    Declaration of simple RGBA color structure.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include <type_traits>
#include <cstdint>
#include <array>

namespace toxico {
    struct Color4 {
        static constexpr uint8_t channels = 4;

        fp_type r, g, b, a;

        /**
         * @brief Constructor.
         * 
         * @param r Red component   (0.0 - 1.0)
         * @param g Green component (0.0 - 1.0)
         * @param b Blue component  (0.0 - 1.0)
         * @param a Alpha component (0.0 - 1.0)
         */
        Color4(fp_type r, fp_type g, fp_type b, fp_type a) noexcept;

        /**
         * @brief Constructor.
         */
        Color4() noexcept;

        /**
         * @brief Gets a fully transparent color.
         * 
         * @return A fully transparent color.
         */
        static Color4 transparent() noexcept;

        /**
         * @brief Creates a Color4 from RGBA8 format.
         * 
         * @param r The red color channel.
         * @param g The green color channel.
         * @param b The blue color channel.
         * @param a The red color channel.
         * @return The appropriate Color4 object.
         */
        static Color4 fromRGBA8(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept;

        /**
         * @brief Converts a Color4 to RGBA8 format.
         * 
         * @return The four color channels of this color in RGBA8 format.
         */
        std::array<uint8_t, Color4::channels> toRGBA8() const noexcept;

        /**
         * @brief Gets the color at the desired channel.
         * 
         * @param channel The desired channel.
         * @return The value of the desired channel.
         * 
         * 0 -> Red
         * 1 -> Green
         * 2 -> Blue
         * 3 -> Alpha
         */
        fp_type operator[](std::size_t channel) const;
        fp_type& operator[](std::size_t channel);

        /**
         * @brief Gets the color at the desired channel.
         * 
         * @param channel The desired channel.
         * @return The value of the desired channel.
         * 
         * Throws an invalid argument error if an invalid channel is passed.
         * 0 -> Red
         * 1 -> Green
         * 2 -> Blue
         * 3 -> Alpha
         */
        fp_type at(std::size_t channel) const;
        fp_type& at(std::size_t channel);

        /**
         * @brief Multiplies this color's RGB channels by a scalar.
         * 
         * @param scalar The scalar the color is being multiplied by.
         * @return The modified color.
         */
        template<typename T>
        requires std::is_arithmetic_v<T>
        Color4& operator*=(T scalar) noexcept;

        /**
         * @brief Multiplies a color's RGB channels by a scalar.
         * 
         * @param scalar The scalar the color is being multiplied by.
         * @return The resulting color.
         */
        template<typename T>
        requires std::is_arithmetic_v<T>
        Color4 operator*(T scalar) const noexcept;

        /**
         * @brief Divides this color's RGB channels by a scalar.
         * 
         * @param scalar The scalar the color is being divided by.
         * @return The modified color.
         */
        template<typename T>
        requires std::is_arithmetic_v<T>
        Color4& operator/=(T scalar) noexcept;

        /**
         * @brief Divides a color's RGB channels by a scalar.
         * 
         * @param scalar The scalar the color is being divided by.
         * @return The resulting color.
         */
        template<typename T>
        requires std::is_arithmetic_v<T>
        Color4 operator/(T scalar) const noexcept;
    };

    /**
     * @brief Multiplies a color's RGB channels by a scalar.
     * 
     * @param scalar The scalar the color is being multiplied by.
     * @return The resulting color.
     */
    template<typename T>
    requires std::is_arithmetic_v<T>
    Color4 operator*(T scalar, const Color4& color) noexcept;
}

#include "visuals/Color4.tpp"
