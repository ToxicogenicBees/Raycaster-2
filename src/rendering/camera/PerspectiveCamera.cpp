/*
    PerspectiveCamera.cpp

    Implementation of a perspective camera.
*/

#include "rendering/camera/PerspectiveCamera.hpp"
#include <cmath>

namespace toxico {
    PerspectiveCamera::PerspectiveCamera(const Transform& transform, fp_type field_of_view) noexcept
        : CameraBase(transform),
          field_of_view_(field_of_view)
    {}

    PerspectiveCamera::PerspectiveCamera(fp_type field_of_view) noexcept
        : field_of_view_(field_of_view)
    {}

    Ray3 PerspectiveCamera::generateRay(const Vector2& location, const Size& render_size) const {
        // Convert the fov to the dimensions of the projection plane at a distance of 1 from the camera
        const fp_type aspect_ratio = static_cast<fp_type>(render_size.width) / static_cast<fp_type>(render_size.height);
        const fp_type half_height = std::tan(field_of_view_ * 0.5);
        const fp_type half_width = half_height * aspect_ratio;

        // Convert pixel coordinates to [0, 1].
        const fp_type u = (location.x + 0.5) / static_cast<fp_type>(render_size.width);
        const fp_type v = (location.y + 0.5) / static_cast<fp_type>(render_size.height);

        // Convert [0, 1] to camera-space coordinates.
        const fp_type x = (u - 0.5) * 2.0 * half_width;
        const fp_type y = (0.5 - v) * 2.0 * half_height;
        
        // Transform the ray from camera space into world space.
        const Vector3 local_direction{x, y, -1.0};
        return Ray3{
            transform.toWorldPoint(Vector3::zero()),
            transform.toWorldVector(local_direction).normal()
        };
    }

    fp_type PerspectiveCamera::fieldOfView() const noexcept {
        return field_of_view_;
    }
}