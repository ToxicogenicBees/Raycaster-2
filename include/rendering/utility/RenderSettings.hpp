/*
    RenderSettings.hpp

    Declaration of a struct of render settings.
*/

#pragma once

#include "rendering/camera/CameraBase.hpp"
#include "rendering/concepts/Shader.hpp"
#include "foundation/geometry/Size.hpp"
#include "scene/Scene.hpp"

namespace toxico {
    template<Shader S>
    struct RenderSettings {
        const Scene& scene;
        const CameraBase& camera;
        const S& shader;
        Size render_size;
        Color3 background = Color3::zero();
    };
}
