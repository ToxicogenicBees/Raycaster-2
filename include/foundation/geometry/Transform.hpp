/*
    Transform.hpp

    Declaration of a transform.
*/

#pragma once

#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Mat4x4.hpp"
#include "foundation/geometry/AABB.hpp"
#include "foundation/math/Vector.hpp"
#include "foundation/math/Ray.hpp"
#include <optional>

namespace toxico {
    class Transform {
    private:
        // Cached transformations
        Mat4x4 matrix_ = Mat4x4::identity();
        Mat4x4 inverse_ = Mat4x4::identity();

        // Transformation values
        Mat4x4 rotation_ = Mat4x4::identity();
        Vector3 position_ = Vector3::zero();
        Vector3 scale_ = Vector3::one();

        /**
         * @brief Updates cached transformations.
         */
        void update_();

    public:
        enum class RotationOrder {
            XYZ,
            XZY,
            YXZ,
            YZX,
            ZXY,
            ZYX
        };

        static const Vector3 local_forward;
        static const Vector3 local_right;
        static const Vector3 local_up;

        /**
         * @brief Constructor.
         */
        Transform() = default;

        /**
         * @brief Applies a translation to the transform in world-space.
         * 
         * @param translation The desired translation.
         */
        void translate(const Vector3& translation) noexcept;

        /**
         * @brief Applies a translation to the transform in local-space.
         * 
         * @param translation The desired translation.
         */
        void translateLocal(const Vector3& translation) noexcept;

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
         * @param order The desired rotation order (default is XYZ).
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

        /**
         * @brief Rotates the transform to face a position.
         * 
         * @param target The position to focus the transform on.
         * @param up The desired up-vector (default is the y-axis)
         */
        void lookAt(const Vector3& target, const Vector3& up = Vector3::yAxis());

        /**
         * @brief Gets the position of the transform.
         * 
         * @return The position of the transform.
         */
        const Vector3& position() const noexcept;

        /**
         * @brief Gets the scale of the transform.
         * 
         * @return The scale of the transform.
         */
        const Vector3& scale() const noexcept;

        /**
         * @brief Gets the rotation of the transform.
         * 
         * @return The rotation of the transform.
         */
        const Mat4x4& rotation() const noexcept;

        /**
         * @brief Gets the forward vector of this transform.
         * 
         * @return The forward vector of this transform.
         */
        Vector3 forward() const;

        /**
         * @brief Gets the right vector of this transform.
         * 
         * @return The right vector of this camera.
         */
        Vector3 right() const;

        /**
         * @brief Gets the up vector of this transform.
         * 
         * @return The up vector of this transform.
         */
        Vector3 up() const;

        /**
         * @brief Converts a point from local space to world space.
         * 
         * @param point The point being converted.
         * @return The point in local space.
         */
        Vector3 toLocalPoint(const Vector3& point) const;

        /**
         * @brief Converts a vector from local space to world space.
         * 
         * @param point The vector being converted.
         * @return The vector in local space.
         */
        Vector3 toLocalVector(const Vector3& vector) const;

        /**
         * @brief Converts a normal vector from local space to world space.
         * 
         * @param point The normal vector being converted.
         * @return The normal vector in local space.
         */
        Vector3 toLocalNormal(const Vector3& normal) const;

        /**
         * @brief Converts a ray from local space to world space.
         * 
         * @param point The ray being converted.
         * @return The ray in local space.
         */
        Ray3 toLocal(const Ray3& ray) const;

        /**
         * @brief Converts an AABB from local space to world space.
         * 
         * @param point The AABB being converted.
         * @return The AABB in local space.
         */
        AABB toLocal(const AABB& ray) const;

        /**
         * @brief Converts a point from world space to local space.
         * 
         * @param point The point being converted.
         * @return The point in local space.
         */
        Vector3 toWorldPoint(const Vector3& point) const;

        /**
         * @brief Converts a vector from world space to local space.
         * 
         * @param point The vector being converted.
         * @return The vector in local space.
         */
        Vector3 toWorldVector(const Vector3& vector) const;

        /**
         * @brief Converts a normal vector from world space to local space.
         * 
         * @param point The normal vector being converted.
         * @return The normal vector in local space.
         */
        Vector3 toWorldNormal(const Vector3& normal) const;

        /**
         * @brief Converts a ray from world space to local space.
         * 
         * @param point The ray being converted.
         * @return The ray in local space.
         */
        Ray3 toWorld(const Ray3& ray) const;

        /**
         * @brief Converts an AABB from world space to local space.
         * 
         * @param point The AABB being converted.
         * @return The AABB in local space.
         */
        AABB toWorld(const AABB& ray) const;
    };
}
