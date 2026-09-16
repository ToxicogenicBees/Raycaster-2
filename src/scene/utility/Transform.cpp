/*
    Transform.cpp

    Implementation of a transform.
*/

#include "scene/utility/Transform.hpp"

namespace {
    Vector3 applyPoint(const Mat4x4& mat, const Vector3& point) {
        const Vector4 transformed{
            point.x * mat.at(0, 0) + point.y * mat.at(0, 1) + point.z * mat.at(0, 2) + mat.at(0, 3),
            point.x * mat.at(1, 0) + point.y * mat.at(1, 1) + point.z * mat.at(1, 2) + mat.at(1, 3),
            point.x * mat.at(2, 0) + point.y * mat.at(2, 1) + point.z * mat.at(2, 2) + mat.at(2, 3),
            point.x * mat.at(3, 0) + point.y * mat.at(3, 1) + point.z * mat.at(3, 2) + mat.at(3, 3)
        };

        return {
            transformed.x / transformed.w,
            transformed.y / transformed.w,
            transformed.z / transformed.w
        };
    }

    Vector3 applyVector(const Mat4x4& mat, const Vector3& vector) {
        return {
            vector.x * mat.at(0, 0) + vector.y * mat.at(0, 1) + vector.z * mat.at(0, 2),
            vector.x * mat.at(1, 0) + vector.y * mat.at(1, 1) + vector.z * mat.at(1, 2),
            vector.x * mat.at(2, 0) + vector.y * mat.at(2, 1) + vector.z * mat.at(2, 2)
        };
    }
}

namespace toxico {
    Transform::Transform()
        : matrix_(Mat4x4::identity()),
          inverse_(matrix_)
    {}
    
    void Transform::translate(const Vector3& translation) noexcept {
        auto transform = Mat4x4::identity();
        transform(0, 3) = translation.x;
        transform(1, 3) = translation.y;
        transform(2, 3) = translation.z;

        matrix_ = transform * matrix_;
        inverse_.reset();
    }

    void Transform::rotateX(fp_type rot_x) noexcept {
        auto transform = Mat4x4::identity();
        auto sin = std::sin(rot_x);
        auto cos = std::cos(rot_x);

        transform(1, 1) = cos;
        transform(1, 2) = -sin;
        transform(2, 1) = sin;
        transform(2, 2) = cos;

        matrix_ = transform * matrix_;
        inverse_.reset();
    }

    void Transform::rotateY(fp_type rot_y) noexcept {
        auto transform = Mat4x4::identity();
        auto sin = std::sin(rot_y);
        auto cos = std::cos(rot_y);

        transform(0, 0) = cos;
        transform(0, 2) = sin;
        transform(2, 0) = -sin;
        transform(2, 2) = cos;

        matrix_ = transform * matrix_;
        inverse_.reset();
    }

    void Transform::rotateZ(fp_type rot_z) noexcept {
        auto transform = Mat4x4::identity();
        auto sin = std::sin(rot_z);
        auto cos = std::cos(rot_z);

        transform(0, 0) = cos;
        transform(0, 1) = -sin;
        transform(1, 0) = sin;
        transform(1, 1) = cos;

        matrix_ = transform * matrix_;
        inverse_.reset();
    }

    void Transform::rotate(const Vector3& rotation, RotationOrder order) noexcept {
        switch(order) {
        case(RotationOrder::XYZ):
            rotateX(rotation.x);
            rotateY(rotation.y);
            rotateZ(rotation.z);
            break;

        case(RotationOrder::XZY):
            rotateX(rotation.x);
            rotateZ(rotation.z);
            rotateY(rotation.y);
            break;

        case(RotationOrder::YXZ):
            rotateY(rotation.y);
            rotateX(rotation.x);
            rotateZ(rotation.z);
            break;

        case(RotationOrder::YZX):
            rotateY(rotation.y);
            rotateZ(rotation.z);
            rotateX(rotation.x);
            break;

        case(RotationOrder::ZXY):
            rotateZ(rotation.z);
            rotateX(rotation.x);
            rotateY(rotation.y);
            break;

        case(RotationOrder::ZYX):
            rotateZ(rotation.z);
            rotateY(rotation.y);
            rotateX(rotation.x);
            break;
        }
    }

    void Transform::scale(const Vector3& scale_factor) noexcept {
        auto transform = Mat4x4::identity();
        transform(0, 0) = scale_factor.x;
        transform(1, 1) = scale_factor.y;
        transform(2, 2) = scale_factor.z;

        matrix_ = transform * matrix_;
        inverse_.reset();
    }

    void Transform::scale(fp_type scale_factor) noexcept {
        scale(scale_factor * Vector3::one());
    }

    Vector3 Transform::toLocalPoint(const Vector3& point) const {
        if (!inverse_)
            inverse_ = matrix_.inverse();

        return applyPoint(inverse_.value(), point);
    }

    Vector3 Transform::toLocalVector(const Vector3& vector) const {
        if (!inverse_)
            inverse_ = matrix_.inverse();

        return applyVector(inverse_.value(), vector);
    }

    Vector3 Transform::toLocalNormal(const Vector3& normal) const {
        return applyVector(matrix_.transpose(), normal);
    }

    Vector3 Transform::toWorldPoint(const Vector3& point) const {
        return applyPoint(matrix_, point);
    }

    Vector3 Transform::toWorldVector(const Vector3& vector) const {
        return applyVector(matrix_, vector);
    }

    Vector3 Transform::toWorldNormal(const Vector3& normal) const {
        if (!inverse_)
            inverse_ = matrix_.inverse();

        return applyVector(inverse_->transpose(), normal);
    }

    Ray3 Transform::toLocal(const Ray3& ray) const {
        return {
            toLocalPoint(ray.origin),
            toLocalVector(ray.direction)
        };
    }

    Ray3 Transform::toWorld(const Ray3& ray) const {
        return {
            toWorldPoint(ray.origin),
            toWorldVector(ray.direction)
        };
    }
}
