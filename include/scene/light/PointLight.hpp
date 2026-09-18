/*
    PointLight.cpp

    Declaration of a point light.
*/

#pragma once

#include "scene/light/LightBase.hpp"
#include "scene/light/utility/LightProperties.hpp"
#include "scene/light/utility/LightSample.hpp"
#include "foundation/math/Vector.hpp"

namespace toxico {
    struct PointLight final : LightBase {
        /**
         * @brief Constructor.
         * 
         * @param properties The properties of this light.
         */
        PointLight(const LightProperties& properties);

        /**
         * @brief Constructor.
         */
        PointLight() = default;


        /**
         * @brief Gets a sample of this light at a given point.
         * 
         * @param position The world position the light is being sampled at.
         * @return A sample of the light at this position.
         */
        LightSample sample(const Vector3& position) const noexcept final;
    };
}
