/*
    shading.cpp

    Implementation of a set of free functions to help in shading.
*/

#include "rendering/shader/utility/shading.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Ray.hpp"
#include "tracing/raytrace.hpp"

namespace toxico::shading {
    bool castsShadow(const Scene& scene, const LightSample& light_sample, const SceneTrace& trace) {
        const auto normal = (trace.front_face ? trace.geometric_normal : -trace.geometric_normal);
        constexpr fp_type epsilon = 1e-5;
        const auto to_light = Ray3{
            trace.point + epsilon * normal,
            -light_sample.direction
        };

        const auto to_light_trace = raytrace::trace(to_light, scene, epsilon, light_sample.distance - epsilon);
        return to_light_trace.has_value();
    }

    Vector3 reflect(const Vector3 v, const Vector3 n) {
        return v - fp_type{2.0} * v.dot(n) * n;
    }
}
