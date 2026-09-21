/*
    RecursivePhongShader.cpp

    Implementation of a Phong shader.
*/

#include "rendering/shader/RecursivePhongShader.hpp"
#include "rendering/shader/utility/PhongProperties.hpp"
#include "rendering/shader/utility/shading.hpp"
#include "tracing/raytrace.hpp"

namespace {
    constexpr toxico::fp_type EPSILON = 1e-5;
}

namespace toxico {
    Color3 RecursivePhongShader::shade_(const Ray3& ray, const Scene& scene, const Color3& background, uint8_t depth) const noexcept {
        if (depth >= MAX_DEPTH_)
            return background;

        const auto trace = raytrace::trace(ray, scene);
        if (!trace)
            return background;

        const auto* material = scene.materials.resolve(trace->object.material);
        if (!material)
            return background;
        const auto material_sample = material->sample(trace->uv);

        // -------------------------------------------------------------------------
        // Local Phong shading
        // -------------------------------------------------------------------------

        // Fetch properties
        PhongProperties properties(material_sample);

        // Fetch the ambient contribution
        Color3 simple_color = properties.ambient * scene.ambience.intensity * scene.ambience.color;

        // Fetch contribution from each light
        for (const auto& light : scene.lights) {
            // Fetch the light sample at the intersection
            const auto light_sample = light.sample(trace->point);
            
            // Fetch the light's diffusive contribution
            const Color3 visibility = shading::transmissiveShadow(scene, light_sample, *trace);
            const fp_type n_dot_l = std::max(fp_type{0.0}, -light_sample.direction.dot(trace->shading_normal));
            if (n_dot_l > fp_type{0.0})
                simple_color += properties.diffuse * light_sample.color * n_dot_l * visibility;

            // Fetch the light's specular contribution
            const Vector3 view_direction = -ray.direction;
            const Vector3 reflection = shading::reflect(light_sample.direction, trace->shading_normal);
            const fp_type r_dot_v = std::max(fp_type{0.0}, reflection.dot(view_direction));
            simple_color += properties.specular * light_sample.color * std::pow(r_dot_v, properties.shininess);
        }

        // -------------------------------------------------------------------------
        // Surface orientation
        // -------------------------------------------------------------------------

        const Vector3 geometric_normal = trace->front_face ? trace->geometric_normal : -trace->geometric_normal;
        const Vector3 shading_normal = trace->shading_normal;

        // -------------------------------------------------------------------------
        // Material properties
        // -------------------------------------------------------------------------

        const fp_type metallic = std::clamp(material_sample.metallic, fp_type{0}, fp_type{1});
        const fp_type transmission = std::clamp(material_sample.transmission, fp_type{0}, fp_type{1}) * (1.0 - metallic);
        const fp_type ior = std::max(material_sample.ior, fp_type{1.0});

        // -------------------------------------------------------------------------
        // Fresnel
        // -------------------------------------------------------------------------

        const fp_type cos_theta = std::clamp(-ray.direction.dot(geometric_normal), fp_type{0}, fp_type{1});

        const fp_type f0_ratio = (ior - 1.0) / (ior + 1.0);
        const fp_type f0 = f0_ratio * f0_ratio;

        const fp_type fresnel = f0 + (1.0 - f0) * std::pow(1.0 - cos_theta, 5.0);

        // -------------------------------------------------------------------------
        // Reflection
        // -------------------------------------------------------------------------

        Color3 reflection_weight =
            Color3(1, 1, 1) * (fresnel * (1.0 - metallic))
            + material_sample.base_color * metallic;

        Color3 reflected_color = Color3(0, 0, 0);

        const fp_type max_reflection_weight = std::max(reflection_weight.r, std::max(reflection_weight.g, reflection_weight.b));
        if (max_reflection_weight > fp_type{0}) {
            const Ray3 reflected_ray{
                trace->point + EPSILON * geometric_normal,
                shading::reflect(ray.direction, shading_normal).normal()
            };

            reflected_color = shade_(reflected_ray, scene, background, depth + 1);
        }

        // -------------------------------------------------------------------------
        // Transmission / refraction
        // -------------------------------------------------------------------------

        Color3 transmission_weight = Color3(0, 0, 0);
        Color3 transmitted_color = Color3(0, 0, 0);
        if (transmission > fp_type{0}) {
            const fp_type eta_i = trace->front_face ? fp_type{1.0} : ior;
            const fp_type eta_t = trace->front_face ? ior : fp_type{1.0};
            const fp_type eta = eta_i / eta_t;

            const fp_type transmitted_energy = transmission * (1.0 - fresnel);
            const fp_type reflected_dielectric_energy = fresnel;

            const auto refracted = shading::refract(ray.direction, geometric_normal, eta);
            if (refracted) {
                reflection_weight = Color3(1, 1, 1) *
                    (reflected_dielectric_energy * (1.0 - metallic))
                    + material_sample.base_color * metallic;

                const Ray3 transmitted_ray{
                    trace->point - EPSILON * geometric_normal,
                    refracted->normal()
                };
                transmitted_color = shade_(transmitted_ray, scene, background, depth + 1);

                transmission_weight = Color3(1, 1, 1) * transmitted_energy;
            }
            else {
                // TIR: all dielectric energy is reflected.
                reflection_weight = Color3(1, 1, 1) * (1.0 - metallic)
                    + material_sample.base_color * metallic;

                transmission_weight = Color3(0, 0, 0);
            }
        }

        // -------------------------------------------------------------------------
        // Remaining local contribution
        // -------------------------------------------------------------------------

        const Color3 local_weight = Color3(1, 1, 1) - reflection_weight - transmission_weight;

        // -------------------------------------------------------------------------
        // Combine
        // -------------------------------------------------------------------------

        return local_weight * simple_color
            + reflection_weight * reflected_color
            + transmission_weight * transmitted_color;
    }

    Color3 RecursivePhongShader::shade(const Ray3& ray, const Scene& scene, const Color3& background) const noexcept {
        return shade_(ray, scene, background, 0);
    }
}
