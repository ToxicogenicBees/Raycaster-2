/*
    OrthographicCamera.cpp

    Implementation of an orthographic camera.
*/

#include "rendering/camera/OrthographicCamera.hpp"

namespace toxico {
    OrthographicCamera::OrthographicCamera(const Transform& transform, fp_type view_height) noexcept
        : CameraBase(transform),
          view_height_(view_height)
    {}

    OrthographicCamera::OrthographicCamera(fp_type view_height) noexcept
        : view_height_(view_height) {}

    Ray3 OrthographicCamera::generateRay(const Vector2& location, const Size& render_size) const {
        // Fetch view width
        fp_type aspect_ratio = static_cast<fp_type>(render_size.width) / static_cast<fp_type>(render_size.height);
        const fp_type view_width = view_height_ * aspect_ratio;

        // Convert pixel coordinates to [0, 1].
        const fp_type u = location.x / static_cast<fp_type>(render_size.width);
        const fp_type v = location.y / static_cast<fp_type>(render_size.height);

        // Convert [0, 1] to camera-space coordinates.
        const fp_type x = (u - 0.5) * view_width;
        const fp_type y = (0.5 - v) * view_height_;
        
        // Create the desired ray
        const Vector3 local_origin(x, y, 0.0);
        return Ray3{
            transform.toWorldPoint(local_origin),
            transform.forward()
        };
    }

    fp_type OrthographicCamera::viewHeight() const noexcept {
        return view_height_;
    }
}
