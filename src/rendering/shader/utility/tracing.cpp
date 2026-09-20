/*
    tracing.cpp

    Implementation of a set of free functions to help in tracing.
*/

#include "rendering/shader/utility/tracing.hpp"
#include "foundation/math/Ray.hpp"

namespace toxico::tracing {
    bool castsShadow(const Scene& scene, const LightSample& light_sample, const SurfaceInteraction& interaction) {
        const fp_type epsilon = 1e-5;
        const auto to_light = Ray3{
            interaction.point + epsilon * interaction.shading_normal,
            light_sample.direction
        };

        const auto to_light_interaction = scene.intersect(to_light, epsilon, light_sample.distance - epsilon);
        return to_light_interaction.has_value();
    }

    Vector3 reflect(const Vector3 vector, const Vector3 normal) {
        return 2 * vector.dot(normal) * normal - vector;
    }
}
