/*
    Shader.hpp

    Declaration of a concept for a shader.
*/

#pragma once

#include "foundation/math/Ray.hpp"
#include "visuals/Color4.hpp"
#include "scene/Scene.hpp"
#include <concepts>

namespace toxico {
    template<typename T>
    concept Shader = requires(const T& shader, const Ray3& ray, const Scene& scene, const Color4& background) {
        // Must define the following shading method
        { shader.shade(ray, scene, background) } -> std::same_as<Color4>;
    };
}
