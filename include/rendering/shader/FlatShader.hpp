/*
    FlatShader.hpp

    Declaration of a flat shader.
*/

#pragma once

#include "foundation/math/Ray.hpp"
#include "visuals/Color3.hpp"
#include "scene/Scene.hpp"

namespace toxico {
    struct FlatShader {
        /**
         * @brief Calculates the color for a ray traveling through a scene.
         * 
         * @param ray The ray being followed.
         * @param scene The scene the ray is traveling through.
         * @param background The desired background color.
         * @return The resulting color this ray's observer would see.
         */
        Color3 shade(const Ray3& ray, const Scene& scene, const Color3& background) const noexcept;
    };
}
