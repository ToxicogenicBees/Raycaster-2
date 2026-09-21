/*
    Color3.hpp

    Declaration of simple RGB color structure.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include <cstdint>
#include <array>

namespace toxico {
    struct Color3 {
        static constexpr uint8_t channels = 3;
        fp_type r, g, b;

        /**
         * @brief Constructor.
         * 
         * @param r Red component   (0.0 - 1.0)
         * @param g Green component (0.0 - 1.0)
         * @param b Blue component  (0.0 - 1.0)
         */
        Color3(fp_type r, fp_type g, fp_type b) noexcept;

        /**
         * @brief Constructor.
         */
        Color3() noexcept;

        /**
         * @brief Creates a Color3 with all components being 0.
         * 
         * @return A Color3 with all components being 0.
         */
        static Color3 zero() noexcept;

        /**
         * @brief Creates a Color3 with all components being 1.
         * 
         * @return A Color3 with all components being 1.
         */
        static Color3 one() noexcept;

        /**
         * @brief Creates a Color3 from RGBA8 format.
         * 
         * @param r The red color channel.
         * @param g The green color channel.
         * @param b The blue color channel.
         * @return The appropriate Color3 object.
         */
        static Color3 fromRGB8(uint8_t r, uint8_t g, uint8_t b) noexcept;

        /**
         * @brief Converts a Color3 to RGBA8 format.
         * 
         * @return The four color channels of this color in RGBA8 format.
         */
        std::array<uint8_t, Color3::channels> toRGB8() const noexcept;

        /**
         * @brief Gets the color at the desired channel.
         * 
         * @param channel The desired channel.
         * @return The value of the desired channel.
         * 
         * 0 -> Red
         * 1 -> Green
         * 2 -> Blue
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
         */
        fp_type at(std::size_t channel) const;
        fp_type& at(std::size_t channel);

        /**
         * @brief Multiplies this color by a scalar.
         * 
         * @param scalar The scalar the color is being multiplied by.
         * @return The modified color.
         */
        template<typename T>
        requires std::is_arithmetic_v<T>
        Color3& operator*=(T scalar) noexcept;

        /**
         * @brief Multiplies a color by a scalar.
         * 
         * @param scalar The scalar the color is being multiplied by.
         * @return The resulting color.
         */
        template<typename T>
        requires std::is_arithmetic_v<T>
        Color3 operator*(T scalar) const noexcept;

        /**
         * @brief Divides this color by a scalar.
         * 
         * @param scalar The scalar the color is being divided by.
         * @return The modified color.
         */
        template<typename T>
        requires std::is_arithmetic_v<T>
        Color3& operator/=(T scalar) noexcept;

        /**
         * @brief Divides a color by a scalar.
         * 
         * @param scalar The scalar the color is being divided by.
         * @return The resulting color.
         */
        template<typename T>
        requires std::is_arithmetic_v<T>
        Color3 operator/(T scalar) const noexcept;

        /**
         * @brief Multiplies the channels of another color to this color.
         * 
         * @param other Another color.
         * @return The modified color.
         */
        Color3& operator*=(const Color3 other) noexcept;

        /**
         * @brief Multiplies the channels of two colors together.
         * 
         * @param other Another color.
         * @return The resulting color.
         */
        Color3 operator*(const Color3 other) const noexcept;

        /**
         * @brief Adds the channels of another color to this color.
         * 
         * @param other Another color.
         * @return The modifier color.
         */
        Color3& operator+=(const Color3& other) noexcept;

        /**
         * @brief Adds the channels of two colors together.
         * 
         * @param other Another color.
         * @return The resulting color.
         */
        Color3 operator+(const Color3& other) const noexcept;

        /**
         * @brief Subtracts the channels of another color to this color.
         * 
         * @param other Another color.
         * @return The modifier color.
         */
        Color3& operator-=(const Color3& other) noexcept;

        /**
         * @brief Subtracts the channels of two colors together.
         * 
         * @param other Another color.
         * @return The resulting color.
         */
        Color3 operator-(const Color3& other) const noexcept;
    };

    /**
     * @brief Multiplies a color by a scalar.
     * 
     * @param scalar The scalar the color is being multiplied by.
     * @return The resulting color.
     */
    template<typename T>
    requires std::is_arithmetic_v<T>
    Color3 operator*(T scalar, const Color3& color) noexcept;
}

#include "visuals/Color3.tpp"
