/*
    Spotlight.cpp

    Implementation of a spotlight.
*/

#include "scene/light/Spotlight.hpp"
#include "foundation/utility/fp_type.hpp"
#include <algorithm>
#include <numbers>
#include <cmath>

namespace toxico {
    Spotlight::Spotlight(fp_type inner_angle, fp_type outer_angle, const LightProperties& properties)
        : LightBase(properties),
          inner_angle(std::clamp(inner_angle, fp_type{0}, fp_type{std::numbers::pi})),
          outer_angle(std::clamp(outer_angle, fp_type{0}, fp_type{std::numbers::pi}))
    {}

    Spotlight::Spotlight(fp_type cone_angle, const LightProperties& properties)
        : LightBase(properties),
          inner_angle(std::clamp(cone_angle, fp_type{0}, fp_type{std::numbers::pi})),
          outer_angle(inner_angle)
    {}

    Spotlight::Spotlight(fp_type inner_angle, fp_type outer_angle)
        : inner_angle(std::clamp(inner_angle, fp_type{0}, fp_type{std::numbers::pi})),
          outer_angle(std::clamp(outer_angle, fp_type{0}, fp_type{std::numbers::pi}))
    {}

    Spotlight::Spotlight(fp_type cone_angle)
        : inner_angle(std::clamp(cone_angle, fp_type{0}, fp_type{std::numbers::pi})),
          outer_angle(inner_angle)
    {}

    LightSample Spotlight::sample(const Vector3& position) const noexcept {
        // Fetch the distance traveled
        const auto offset = transform.position() - position;
        const auto distance = offset.magnitude();
        
        // Fetch the angle between the light's facing direction and the point the light is checking
        const auto light_dir = offset.normal();
        const auto look_dir = transform.forward();
        const auto point_dir = -light_dir;
        const fp_type cos_angle = look_dir.dot(point_dir);
        
        // Fetch the desired intensity
        const fp_type cos_inner = std::cos(0.5 * inner_angle);
        const fp_type cos_outer = std::cos(0.5 * outer_angle);
        const fp_type t = std::clamp(
            (cos_angle - cos_outer) / (cos_inner - cos_outer),
            fp_type{0},
            fp_type{1}
        );
        const fp_type intensity = t * properties.intensity;

        // Fetch the desired attenuation
        const fp_type attenuation = 1.0 / properties.attenuation.evaluate(distance);

        return LightSample{
            .direction = light_dir,
            .color = properties.color * intensity * attenuation,
            .distance = distance
        };
    }
}
