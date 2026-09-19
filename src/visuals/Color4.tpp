/*
    Color4.tpp

    Template implementation of simple RGBA color structure.
*/

namespace toxico {
    template<typename T>
    requires std::is_arithmetic_v<T>
    Color4& Color4::operator*=(T scalar) noexcept {
        r *= static_cast<fp_type>(scalar);
        g *= static_cast<fp_type>(scalar);
        b *= static_cast<fp_type>(scalar);
        return *this;
    }
    
    template<typename T>
    requires std::is_arithmetic_v<T>
    Color4 Color4::operator*(T scalar) const noexcept {
        return Color4{
            r * static_cast<fp_type>(scalar),
            g * static_cast<fp_type>(scalar),
            b * static_cast<fp_type>(scalar)
        };
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    Color4& Color4::operator/=(T scalar) noexcept {
        r /= static_cast<fp_type>(scalar);
        g /= static_cast<fp_type>(scalar);
        b /= static_cast<fp_type>(scalar);
        return *this;
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    Color4 Color4::operator/(T scalar) const noexcept {
        return Color4{
            r / static_cast<fp_type>(scalar),
            g / static_cast<fp_type>(scalar),
            b / static_cast<fp_type>(scalar)
        };
    }
    
    template<typename T>
    requires std::is_arithmetic_v<T>
    Color4 operator*(T scalar, const Color4& color) noexcept {
        return Color4{
            color.r * static_cast<fp_type>(scalar),
            color.g * static_cast<fp_type>(scalar),
            color.b * static_cast<fp_type>(scalar)
        };
    }
}
