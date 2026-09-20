/*
    FlatShader.cpp

    Implementation of a flat shader.
*/

#include "rendering/shader/FlatShader.hpp"

namespace toxico {
    Color3 FlatShader::shade(const Ray3& ray, const Scene& scene, const Color3& background) const noexcept {
        // Check if an intersection was found
        const auto result = scene.intersect(ray);

        // Intersection found, use object color
        if (result) {
            const auto* material = scene.materials.resolve(result->object.material);
            if (!material)
                return background;
            return material->sample(result->uv).base_color;
        }

        // Intersection not found, use background color
        return background;
    }
}
