/*
    PointLight.cpp

    Implementation of a point light.
*/

#include "scene/light/PointLight.hpp"

namespace toxico {
    PointLight::PointLight(const Color3& color, fp_type intensity)
        : LightBase(color, intensity) {}

    PointLight::PointLight(const Color3& color)
        : LightBase(color) {}

    LightSample PointLight::sample(const Vector3& position) const noexcept {
        auto offset = position - transform.position();
        return LightSample{
            .direction = offset.normal(),
            .color = color,
            .distance = offset.magnitude()
        };
    }
}
