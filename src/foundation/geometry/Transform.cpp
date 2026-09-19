/*
    Transform.cpp

    Implementation of a transform.
*/

#include "foundation/geometry/Transform.hpp"

namespace {
    Vector3 applyPoint(const Mat4x4& mat, const Vector3& point) {
        const Vector4 homog_point{
            point.x, point.y, point.z, 1.0
        };
        const Vector4 transformed{
            homog_point.dot(mat.row(0)),
            homog_point.dot(mat.row(1)),
            homog_point.dot(mat.row(2)),
            homog_point.dot(mat.row(3))
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
    const Vector3 Transform::local_forward = -Vector3::zAxis();
    const Vector3 Transform::local_right = Vector3::xAxis();
    const Vector3 Transform::local_up = Vector3::yAxis();

    void Transform::wipeCached_() const noexcept {
        matrix_.reset();
        inverse_.reset();
    }

    void Transform::translate(const Vector3& translation) noexcept {
        position_ += translation;
        wipeCached_();
    }

    void Transform::translateLocal(const Vector3& translation) noexcept {
        position_ += applyPoint(rotation_, translation);
        wipeCached_();
    }

    void Transform::rotateX(fp_type rot_x) noexcept {
        auto transform = Mat4x4::identity();
        auto sin = std::sin(rot_x);
        auto cos = std::cos(rot_x);

        transform(1, 1) = cos;
        transform(1, 2) = -sin;
        transform(2, 1) = sin;
        transform(2, 2) = cos;

        rotation_ = transform * rotation_;
        wipeCached_();
    }

    void Transform::rotateY(fp_type rot_y) noexcept {
        auto transform = Mat4x4::identity();
        auto sin = std::sin(rot_y);
        auto cos = std::cos(rot_y);

        transform(0, 0) = cos;
        transform(0, 2) = sin;
        transform(2, 0) = -sin;
        transform(2, 2) = cos;

        rotation_ = transform * rotation_;
        wipeCached_();
    }

    void Transform::rotateZ(fp_type rot_z) noexcept {
        auto transform = Mat4x4::identity();
        auto sin = std::sin(rot_z);
        auto cos = std::cos(rot_z);

        transform(0, 0) = cos;
        transform(0, 1) = -sin;
        transform(1, 0) = sin;
        transform(1, 1) = cos;

        rotation_ = transform * rotation_;
        wipeCached_();
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
        scale_.x *= scale_factor.x;
        scale_.y *= scale_factor.y;
        scale_.z *= scale_factor.z;
        wipeCached_();
    }

    void Transform::scale(fp_type scale_factor) noexcept {
        scale_ *= scale_factor;
        wipeCached_();
    }

    void Transform::lookAt(const Vector3& target, const Vector3& up) {
        // Get the current position of this transform
        const Vector3 position = toWorldPoint(Vector3::zero());

        // Calculate forward, right, and up vectors
        const Vector3 forward = (target - position).normal();
        const Vector3 right = forward.cross(up).normal();
        const Vector3 corrected_up = right.cross(forward);

        // Update the rotation matrix;
        rotation_ = Mat4x4::identity();
        rotation_(0, 0) = right.x;
        rotation_(1, 0) = right.y;
        rotation_(2, 0) = right.z;
        rotation_(0, 1) = corrected_up.x;
        rotation_(1, 1) = corrected_up.y;
        rotation_(2, 1) = corrected_up.z;
        rotation_(0, 2) = -forward.x;
        rotation_(1, 2) = -forward.y;
        rotation_(2, 2) = -forward.z;
        wipeCached_();
    }

    const Vector3& Transform::position() const noexcept {
        return position_; 
    }

    const Vector3& Transform::scale() const noexcept {
        return scale_; 
    }

    const Mat4x4& Transform::rotation() const noexcept {
        return rotation_; 
    }

    Vector3 Transform::forward() const {
        return applyVector(rotation_, Transform::local_forward);
    }

    Vector3 Transform::right() const {
        return applyVector(rotation_, Transform::local_right);
    }

    Vector3 Transform::up() const {
        return applyVector(rotation_, Transform::local_up);
    }

    Vector3 Transform::toLocalPoint(const Vector3& point) const {
        update();
        return applyPoint(inverse_.value(), point);
    }

    Vector3 Transform::toLocalVector(const Vector3& vector) const {
        update();
        return applyVector(inverse_.value(), vector);
    }

    Vector3 Transform::toLocalNormal(const Vector3& normal) const {
        update();
        return applyVector(matrix_->transpose(), normal);
    }

    Ray3 Transform::toLocal(const Ray3& ray) const {
        return {
            toLocalPoint(ray.origin),
            toLocalVector(ray.direction)
        };
    }

    AABB Transform::toLocal(const AABB& aabb) const {
        // Fetch all 8 corners of the bounding box
        const auto min = aabb.lowerBound();
        const auto max = aabb.upperBound();
        std::array<Vector3, 8> corners;
        for (std::size_t i = 0; i < 8; ++i) {
            corners[i].x = ((i & 0x1) ? max.x : min.x);
            corners[i].y = ((i & 0x2) ? max.y : min.y);
            corners[i].z = ((i & 0x4) ? max.z : min.z);
        }

        // Create a bound around the resulting transformed corners
        AABB result;
        for (const auto& corner : corners)
            result.expand(toLocalPoint(corner));
        return result;
    }

    Vector3 Transform::toWorldPoint(const Vector3& point) const {
        update();
        return applyPoint(matrix_.value(), point);
    }

    Vector3 Transform::toWorldVector(const Vector3& vector) const {
        update();
        return applyVector(matrix_.value(), vector);
    }

    Vector3 Transform::toWorldNormal(const Vector3& normal) const {
        update();
        return applyVector(inverse_->transpose(), normal);
    }

    Ray3 Transform::toWorld(const Ray3& ray) const {
        return {
            toWorldPoint(ray.origin),
            toWorldVector(ray.direction)
        };
    }

    AABB Transform::toWorld(const AABB& aabb) const {
        // Fetch all 8 corners of the bounding box
        const auto min = aabb.lowerBound();
        const auto max = aabb.upperBound();
        std::array<Vector3, 8> corners;
        for (std::size_t i = 0; i < 8; ++i) {
            corners[i].x = ((i & 0x1) ? max.x : min.x);
            corners[i].y = ((i & 0x2) ? max.y : min.y);
            corners[i].z = ((i & 0x4) ? max.z : min.z);
        }

        // Create a bound around the resulting transformed corners
        AABB result;
        for (const auto& corner : corners)
            result.expand(toWorldPoint(corner));
        return result;
    }

    void Transform::update() const {
        // Ignore update if the matrices were never wiped
        if (matrix_ && inverse_)
            return;

        // Form translation matrix
        auto translation = Mat4x4::identity();
        translation(0, 3) = position_.x;
        translation(1, 3) = position_.y;
        translation(2, 3) = position_.z;

        // Form scaling matrix
        auto scaling = Mat4x4::identity();
        scaling(0, 0) = scale_.x;
        scaling(1, 1) = scale_.y;
        scaling(2, 2) = scale_.z;

        // Update cached matrices
        matrix_ = translation * scaling * rotation_;
        inverse_ = matrix_->inverse();
    }
}
