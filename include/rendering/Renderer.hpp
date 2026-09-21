/*
    Renderer.hpp

    Declaration of a scene renderer.
*/

#pragma once

#include "rendering/scheduling/JobScheduler.hpp"
#include "rendering/utility/RenderSettings.hpp"
#include "rendering/concepts/Shader.hpp"
#include "visuals/Image.hpp"

namespace toxico {
    class Renderer {
    private:
        JobScheduler scheduler_;

    public:
        /**
         * @brief Renders a scene.
         * 
         * @param settings The desired settings for this render.
         * @return The rendered image.
         */
        template<Shader S>
        Image render(const RenderSettings<S>& settings);
    };
}

#include "rendering/Renderer.tpp"
