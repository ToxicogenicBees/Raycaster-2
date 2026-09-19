/*
    PhongShader.cpp

    Implementation of a Phong shader.
*/

#include "rendering/shaders/PhongShader.hpp"

namespace toxico {
    Color4 PhongShader::shade(const Ray3& ray, const Scene& scene, const Color4& background) const noexcept {
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

        // Fetch the ambient contribution
        Color3 result = material_sample.ambient * scene.ambience.intensity * scene.ambience.color;

        // Fetch contribution from each light
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

            // Fetch the light's specular contribution
            const Vector3 view_direction = -ray.direction;
            const Vector3 reflection = 2 * light_sample.direction.dot(interaction->shading_normal) * interaction->shading_normal - light_sample.direction;
            const fp_type r_dot_v = std::max(fp_type{0.0}, reflection.dot(view_direction));
            result += material_sample.specular * light_sample.color * std::pow(r_dot_v, material_sample.shininess);
        }

        // Return the net light contribution
        return Color4{
            result.r,
            result.g,
            result.b,
            1.0
        };
    }
}
