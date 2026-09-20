/*
    FlatShader.cpp

    Implementation of a flat shader.
*/

#include "rendering/shader/FlatShader.hpp"

namespace toxico {
    Color4 FlatShader::shade(const Ray3& ray, const Scene& scene, const Color4& background) const noexcept {
        // Check if an intersection was found
        const auto result = scene.intersect(ray);

        // Intersection found, use object color
        if (result) {
            const auto* material = scene.materials.resolve(result->object.material);
            const auto color = material->sample(result->uv).base_color;
            return Color4(color, 1.0);
        }

        // Intersection not found, use background color
        return background;
    }
}
