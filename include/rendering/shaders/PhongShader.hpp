/*
    PhongShader.hpp

    Declaration of a Phong shader.
*/

#pragma once

#include "foundation/math/Ray.hpp"
#include "visuals/Color4.hpp"
#include "scene/Scene.hpp"

namespace toxico {
    class PhongShader {
        /**
         * @brief Calculates the color for a ray traveling through a scene.
         * 
         * @param ray The ray being followed.
         * @param scene The scene the ray is traveling through.
         * @param background The desired background color.
         * @return The resulting color this ray's observer would see.
         */
        Color4 shade(const Ray3& ray, const Scene& scene, const Color4& background) const noexcept;
    };
}
