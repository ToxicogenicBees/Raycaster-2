/*
    PointLight.cpp

    Implementation of a point light.
*/

#include "scene/light/PointLight.hpp"
#include "foundation/utility/fp_type.hpp"

namespace toxico {
    PointLight::PointLight(const LightProperties& properties)
        : LightBase(properties) {}

    LightSample PointLight::sample(const Vector3& position) const noexcept {
        const auto offset = transform.position() - position;
        const auto distance = offset.magnitude();
        const fp_type attenuation = 1.0 / properties.attenuation.evaluate(distance);

        return LightSample{
            .direction = offset.normal(),
            .color = properties.color * (properties.intensity * attenuation),
            .distance = distance
        };
    }
}
