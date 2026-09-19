/*
    Renderer.hpp

    Declaration of a scene renderer.
*/

#pragma once

#include "rendering/scheduling/JobScheduler.hpp"
#include "rendering/camera/CameraBase.hpp"
#include "rendering/concepts/Shader.hpp"
#include "foundation/geometry/Size.hpp"
#include "visuals/Color4.hpp"
#include "visuals/Image.hpp"
#include "scene/Scene.hpp"

namespace toxico {
    class Renderer {
    private:
        JobScheduler scheduler_;

    public:
        /**
         * @brief Renders a scene.
         * 
         * @param size The size of the image being rendered.
         * @param scene The scene being rendered.
         * @param camera The camera used to view the scene.
         * @param shader The desired shader.
         * @param background The desired background color for the image.
         * @return The rendered image.
         */
        template<Shader S>
        Image render(const Size& size, const Scene& scene, const CameraBase& camera, const S& shader, const Color4& background);
    };
}

#include "rendering/Renderer.tpp"
