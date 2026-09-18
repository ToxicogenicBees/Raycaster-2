/*
    FlatShader.cpp

    Implementation of a flat shader.
*/

#include "rendering/shaders/FlatShader.hpp"

namespace toxico {
    Color4 FlatShader::shade(const Ray3& ray, const Scene& scene, const Color4& background) const noexcept {
        // Check if an intersection was found
        const auto result = scene.intersect(ray);

        // Intersection found, use object color
        if (result) {
            const auto color = result->object.color;
            return Color4{color.r, color.g, color.b, 1.0};
        }

        // Intersection not found, use background color
        return background;
    }
}
