/*
    Color4.tpp

    Template implementation of simple RGBA color structure.
*/

namespace toxico {
    template<typename T>
    requires std::is_arithmetic_v<T>
    Color4& Color4::operator*=(T scalar) noexcept {
        r *= scalar;
        g *= scalar;
        b *= scalar;
        return *this;
    }
    
    template<typename T>
    requires std::is_arithmetic_v<T>
    Color4 Color4::operator*(T scalar) const noexcept {
        return Color4{
            r * scalar,
            g * scalar,
            b * scalar
        };
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    Color4& Color4::operator/=(T scalar) noexcept {
        r /= scalar;
        g /= scalar;
        b /= scalar;
        return *this;
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    Color4 Color4::operator/(T scalar) const noexcept {
        return Color4{
            r / scalar,
            g / scalar,
            b / scalar
        };
    }
    
    template<typename T>
    requires std::is_arithmetic_v<T>
    Color4 operator*(T scalar, const Color4& color) noexcept {
        return Color4{
            color.r * scalar,
            color.g * scalar,
            color.b * scalar
        };
    }
}
