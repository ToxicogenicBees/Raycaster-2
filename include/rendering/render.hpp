/*
    render.hpp

    Declaration of a free function that renders a scene with a camera into an image.
*/

#pragma once

#include "rendering/camera/CameraBase.hpp"
#include "foundation/geometry/Size.hpp"
#include "visuals/Image.hpp"
#include "scene/Scene.hpp"

namespace toxico::rendering {
    /**
     * @brief Renders a scene to an image.
     * 
     * @param size The size of the render.
     * @param scene The scene being rendered.
     * @param camera The camera used to view the scene.
     */
    Image render(const Size& size, const Scene& scene, const CameraBase& camera);
}
