/*
    Color3.tpp

    Template implementation of simple RGB color structure.
*/

namespace toxico {
    template<typename T>
    requires std::is_arithmetic_v<T>
    Color3& Color3::operator*=(T scalar) noexcept {
        r *= static_cast<fp_type>(scalar);
        g *= static_cast<fp_type>(scalar);
        b *= static_cast<fp_type>(scalar);
        return *this;
    }
    
    template<typename T>
    requires std::is_arithmetic_v<T>
    Color3 Color3::operator*(T scalar) const noexcept {
        return Color3{
            r * static_cast<fp_type>(scalar),
            g * static_cast<fp_type>(scalar),
            b * static_cast<fp_type>(scalar)
        };
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    Color3& Color3::operator/=(T scalar) noexcept {
        r /= static_cast<fp_type>(scalar);
        g /= static_cast<fp_type>(scalar);
        b /= static_cast<fp_type>(scalar);
        return *this;
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    Color3 Color3::operator/(T scalar) const noexcept {
        return Color3{
            r / static_cast<fp_type>(scalar),
            g / static_cast<fp_type>(scalar),
            b / static_cast<fp_type>(scalar)
        };
    }
    
    template<typename T>
    requires std::is_arithmetic_v<T>
    Color3 operator*(T scalar, const Color3& color) noexcept {
        return Color3{
            color.r * static_cast<fp_type>(scalar),
            color.g * static_cast<fp_type>(scalar),
            color.b * static_cast<fp_type>(scalar)
        };
    }
}
