/*
    shading.cpp

    Implementation of a set of free functions to help in shading.
*/

#include "rendering/shader/utility/shading.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Ray.hpp"
#include "tracing/raytrace.hpp"

namespace toxico::shading {
    bool castsShadow(const Scene& scene, const LightSample& light_sample, const SceneTrace& trace) noexcept {
        const auto normal = (trace.front_face ? trace.geometric_normal : -trace.geometric_normal);
        constexpr fp_type epsilon = 1e-5;
        const auto to_light = Ray3{
            trace.point + epsilon * normal,
            -light_sample.direction
        };

        const auto to_light_trace = raytrace::trace(to_light, scene, {epsilon, light_sample.distance - epsilon});
        return to_light_trace.has_value();
    }

    Color3 transmissiveShadow(const Scene& scene, const LightSample& light_sample, const SceneTrace& trace) noexcept {
        constexpr fp_type epsilon = 1e-5;

        Color3 visibility = Color3::one();

        Vector3 origin = trace.point;
        const Vector3 direction = -light_sample.direction;
        fp_type remaining_distance = light_sample.distance;

        constexpr uint8_t max_intersections = 16;
        for (uint8_t i = 0; i < max_intersections; ++i) {
            if (remaining_distance <= epsilon)
                break;

            const Ray3 shadow_ray{
                origin + epsilon * direction,
                direction
            };

            const auto hit = raytrace::trace(shadow_ray, scene, {epsilon, remaining_distance - epsilon});
            if (!hit)
                break;

            const auto* material = scene.materials.resolve(hit->object.material);
            if (!material)
                return Color3::zero();
            const auto sample = material->sample(hit->uv);

            const fp_type transmission =
                std::clamp(
                    sample.transmission,
                    fp_type{0},
                    fp_type{1}
                );

            // Opaque object completely blocks the light
            if (transmission <= fp_type{0})
                return Color3::zero();

            // Transmissive object allows some light through
            visibility *= transmission;

            if (visibility.r <= epsilon && visibility.g <= epsilon && visibility.b <= epsilon)
                return Color3::zero();

            // Continue looking for additional objects between this surface and the light
            remaining_distance -= hit->t;
            origin = hit->point;
        }

        return visibility;
    }

    Vector3 reflect(const Vector3 v, const Vector3 n) noexcept {
        return v - fp_type{2.0} * v.dot(n) * n;
    }

    std::optional<Vector3> refract(const Vector3& v, const Vector3& n, fp_type eta) noexcept {
        const fp_type cos_i = std::clamp(-v.dot(n), fp_type{0}, fp_type{1});
        const fp_type sin2_t = eta * eta * (1.0 - cos_i * cos_i);

        // Total internal reflection.
        if (sin2_t > 1.0)
            return std::nullopt;

        const fp_type cos_t = std::sqrt(1.0 - sin2_t);
        return (
            eta * v
            + (eta * cos_i - cos_t) * n
        ).normal();
    }
}
