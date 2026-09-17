/*
    PointLight.cpp

    Declaration of a point light.
*/

#pragma once

#include "scene/light/LightBase.hpp"
#include "scene/light/utility/LightSample.hpp"
#include "foundation/utility/fp_type.hpp"
#include "visuals/Color3.hpp"

namespace toxico {
    struct PointLight final : LightBase {
        /**
         * @brief Constructor.
         * 
         * @param color The color of the light source.
         * @param intensity The intensity of the light source.
         */
        PointLight(const Color3& color, fp_type intensity);

        /**
         * @brief Constructor.
         * 
         * @param color The color of the light source.
         */
        PointLight(const Color3& color);

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
