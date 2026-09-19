/*
    LambertianShader.cpp

    Implementation of a Lambertian shader.
*/

#include "rendering/shaders/LambertianShader.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Ray.hpp"
#include "visuals/Color3.hpp"
#include <algorithm>

namespace toxico {
    Color4 LambertianShader::shade(const Ray3& ray, const Scene& scene, const Color4& background) const noexcept {
        // Fetch closest intersection
        const auto interaction = scene.intersect(ray);
        if (!interaction)
            return background;

        // Fetch object material
        const auto material_handle = interaction->object.material;
        const auto* material = scene.materials.resolve(material_handle);
        if (!material) {
            // @TODO: Handle missing material
            return background;
        }
        const auto material_sample = material->sample(interaction->uv);

        // Fetch contribution from each light
        Color3 result(0.0, 0.0, 0.0);
        for (const auto& light : scene.lights) {
            // Fetch the light sample at the intersection
            const auto light_sample = light.sample(interaction->point);

            // Check if this light is in shadow
            const fp_type epsilon = 1e-5;
            const auto to_light = Ray3{
                interaction->point + epsilon * interaction->shading_normal,
                light_sample.direction
            };
            if (scene.intersect(to_light, epsilon, light_sample.distance - epsilon)) {
                // Light is obstructed by an object
                continue;
            }

            // Fetch the light's diffusive contribution
            const fp_type n_dot_l = std::max(fp_type{0.0}, light_sample.direction.dot(interaction->shading_normal));
            result += material_sample.diffuse * light_sample.color * n_dot_l;
        }

        // Return the net light contribution
        return Color4(result, 1.0);
    }
}
