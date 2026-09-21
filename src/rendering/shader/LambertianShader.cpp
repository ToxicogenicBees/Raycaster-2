/*
    LambertianShader.cpp

    Implementation of a Lambertian shader.
*/

#include "rendering/shader/LambertianShader.hpp"
#include "rendering/shader/utility/shading.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Ray.hpp"
#include "tracing/raytrace.hpp"
#include "visuals/Color3.hpp"
#include <algorithm>

namespace toxico {
    Color3 LambertianShader::shade(const Ray3& ray, const Scene& scene, const Color3& background) const noexcept {
        // Fetch closest intersection
        const auto trace = raytrace::trace(ray, scene);
        if (!trace)
            return background;

        // Fetch object material
        const auto material_handle = trace->object.material;
        const auto* material = scene.materials.resolve(material_handle);
        if (!material)
            return background;
        const auto material_sample = material->sample(trace->uv);

        // Fetch contribution from each light
        Color3 result(0.0, 0.0, 0.0);
        for (const auto& light : scene.lights) {
            // Fetch the light sample at the intersection
            const auto light_sample = light.sample(trace->point);

            // Check if this light is in shadow
            if (shading::castsShadow(scene, light_sample, *trace))
                continue;

            // Fetch the light's diffusive contribution
            const fp_type n_dot_l = std::max(fp_type{0.0}, -light_sample.direction.dot(trace->shading_normal));
            result += material_sample.base_color * light_sample.color * n_dot_l;
        }

        // Return the net light contribution
        return result;
    }
}
