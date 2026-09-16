/*
    Transform.hpp

    Declaration of a transform.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Mat4x4.hpp"
#include "foundation/math/Vector.hpp"
#include "foundation/math/Ray.hpp"
#include <optional>

namespace toxico {
    enum class RotationOrder {
        XYZ,
        XZY,
        YXZ,
        YZX,
        ZXY,
        ZYX
    };

    class Transform {
    private:
        Mat4x4 matrix_;
        mutable std::optional<Mat4x4> inverse_;

    public:
        enum class RotationOrder {
            XYZ,
            XZY,
            YXZ,
            YZX,
            ZXY,
            ZYX
        };

        /**
         * @brief Applies a translation to the transform.
         * 
         * @param translation The desired translation.
         */
        void translate(const Vector3& translation) noexcept;

        /**
         * @brief Applies a rotation to the transform.
         * 
         * @param rot_x The desired rotation, in radians.
         */
        void rotateX(fp_type rot_x) noexcept;

        /**
         * @brief Applies a rotation to the transform.
         * 
         * @param rot_y The desired rotation, in radians.
         */
        void rotateY(fp_type rot_y) noexcept;

        /**
         * @brief Applies a rotation to the transform.
         * 
         * @param rot_z The desired rotation, in radians.
         */
        void rotateZ(fp_type rot_z) noexcept;

        /**
         * @brief Applies a rotation to the transform.
         * 
         * @param rotation The desired rotation angles, in radians.
         * @param order The desired rotation order.
         */
        void rotate(const Vector3& rotation, RotationOrder order = RotationOrder::XYZ) noexcept;

        /**
         * @brief Applies a scaling factor to the transform.
         * 
         * @param scale_factor The desired scaling factor.
         */
        void scale(const Vector3& scale_factor) noexcept;

        /**
         * @brief Applies a unified scaling factor to the transform.
         * 
         * @param scale_factor The desired unified scaling factor.
         */
        void scale(fp_type scale_factor) noexcept;

        Vector3 toLocalPoint(const Vector3& point) const;
        Vector3 toLocalVector(const Vector3& vector) const;
        Vector3 toLocalNormal(const Vector3& normal) const;

        Vector3 toWorldPoint(const Vector3& point) const;
        Vector3 toWorldVector(const Vector3& vector) const;
        Vector3 toWorldNormal(const Vector3& normal) const;

        Ray3 toLocal(const Ray3& ray) const;
        Ray3 toWorld(const Ray3& ray) const;
    };
}
