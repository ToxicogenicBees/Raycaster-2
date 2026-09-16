/*
    OrthographicCamera.hpp

    Declaration of an orthographic camera.
*/

#pragma once

#include "scene/camera/CameraBase.hpp"
#include "foundation/utility/fp_type.hpp"
#include "scene/utility/Transform.hpp"
#include "foundation/geometry/Size.hpp"
#include "foundation/math/Vector.hpp"
#include "foundation/math/Ray.hpp"

namespace toxico {
    class OrthographicCamera final : public CameraBase {
    private:
        inline static const Vector3 local_direction = -Vector3::zAxis();
        fp_type view_height_;

    public:

        /**
         * @brief Constructor.
         * 
         * @param transform A transform for this camera.
         * @param view_height The view height for this camera.
         */
        OrthographicCamera(const Transform& transform, fp_type view_height) noexcept;

        /**
         * @brief Constructor.
         * 
         * @param view_height The view height for this camera.
         */
        OrthographicCamera(fp_type view_height) noexcept;

        /**
         * @brief Generates a ray through this camera.
         * 
         * @param location The (sub)pixel location the ray starts from.
         * @param render_size The size of the rendered scene, in pixels.
         */
        Ray3 generateRay(const Vector2& location, Size& render_size) const final;

        /**
         * @brief Gets the view height of this camera.
         * 
         * @return The view height of this camera.
         */
        fp_type viewHeight() const noexcept;
    };
}
