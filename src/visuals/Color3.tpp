/*
    Color3.tpp

    Template implementation of simple RGB color structure.
*/

namespace toxico {
    template<typename T>
    requires std::is_arithmetic_v<T>
    Color3& Color3::operator*=(T scalar) noexcept {
        r *= scalar;
        g *= scalar;
        b *= scalar;
        return *this;
    }
    
    template<typename T>
    requires std::is_arithmetic_v<T>
    Color3 Color3::operator*(T scalar) const noexcept {
        return Color3{
            r * scalar,
            g * scalar,
            b * scalar
        };
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    Color3& Color3::operator/=(T scalar) noexcept {
        r /= scalar;
        g /= scalar;
        b /= scalar;
        return *this;
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    Color3 Color3::operator/(T scalar) const noexcept {
        return Color3{
            r / scalar,
            g / scalar,
            b / scalar
        };
    }
    
    template<typename T>
    requires std::is_arithmetic_v<T>
    Color3 operator*(T scalar, const Color3& color) noexcept {
        return Color3{
            color.r * scalar,
            color.g * scalar,
            color.b * scalar
        };
    }
}
