/*
    CameraBase.hpp

    Declaration of an abstract, in-scene camera.
*/

#pragma once

#include "scene/utility/Transform.hpp"
#include "foundation/geometry/Size.hpp"
#include "foundation/math/Vector.hpp"
#include "foundation/math/Ray.hpp"

namespace toxico {
    class CameraBase {
    private:
        Transform transform_;

    public:
        /**
         * @brief Constructor.
         * 
         * @param transform A transform for this camera.
         */
        CameraBase(const Transform& transform) noexcept;

        /**
         * @brief Constructor.
         */
        CameraBase() noexcept = default;

        /**
         * @brief Gets the transform for this camera.
         * 
         * @return The transform for this camera.
         */
        const Transform& transform() const noexcept;
        Transform& transform() noexcept;

        /**
         * @brief Generates a ray through this camera.
         * 
         * @param location The (sub)pixel location the ray starts from.
         * @param render_size The size of the rendered scene, in pixels.
         */
        virtual Ray3 generateRay(const Vector2& location, Size& render_size) const = 0;

        /**
         * @brief Destructor.
         */
        virtual ~CameraBase() = default;
    };
}
