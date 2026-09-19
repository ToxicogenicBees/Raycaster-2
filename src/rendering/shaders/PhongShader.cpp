/*
    PhongShader.cpp

    Implementation of a Phong shader.
*/

#include "rendering/shaders/PhongShader.hpp"
#include "rendering/shaders/utility/PhongProperties.hpp"
#include "rendering/shaders/utility/tracing.hpp"

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

        // Fetch properties
        PhongProperties properties(material_sample);

        // Fetch the ambient contribution
        Color3 result = properties.ambient * scene.ambience.intensity * scene.ambience.color;

        // Fetch contribution from each light
        for (const auto& light : scene.lights) {
            // Fetch the light sample at the intersection
            const auto light_sample = light.sample(interaction->point);

            // Check if this light is in shadow
            if (tracing::castsShadow(scene, light_sample, *interaction))
                continue;

            // Fetch the light's diffusive contribution
            const fp_type n_dot_l = std::max(fp_type{0.0}, light_sample.direction.dot(interaction->shading_normal));
            result += properties.diffuse * light_sample.color * n_dot_l;

            // Fetch the light's specular contribution
            const Vector3 view_direction = -ray.direction;
            const Vector3 reflection = tracing::reflect(light_sample.direction, interaction->shading_normal);
            const fp_type r_dot_v = std::max(fp_type{0.0}, reflection.dot(view_direction));
            result += properties.specular * light_sample.color * std::pow(r_dot_v, properties.shininess);
        }

        // Return the net light contribution
        return Color4(result, 1.0);
    }
}
