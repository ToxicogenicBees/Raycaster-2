/*
    Mat4x4.tpp

    Template implementation of a 4x4 matrix.
*/

namespace toxico {
    template<typename T>
    requires std::is_arithmetic_v<T>
    Mat4x4 Mat4x4::operator*(T s) const {
        Mat4x4 result(*this);
        for (auto& val : result.data_)
            val *= s;
        return result;
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    Mat4x4& Mat4x4::operator*=(T s) {
        for (auto& val : data_)
            val *= s;
        return *this;
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    Mat4x4 Mat4x4::operator/(T s) const {
        Mat4x4 result(*this);
        for (auto& val : result.data_)
            val /= s;
        return result;
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    Mat4x4& Mat4x4::operator/=(T s) {
        for (auto& val : data_)
            val /= s;
        return *this;
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    Mat4x4 operator*(T s, const Mat4x4& mat) {
        Mat4x4 result(mat);
        for (auto& val : result.data_)
            val *= s;
        return result;
    }
}
