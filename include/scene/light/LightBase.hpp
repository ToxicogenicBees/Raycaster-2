/*
    LightBase.hpp

    Declaration of an abstract light source.
*/

#pragma once

#include "scene/light/utility/LightProperties.hpp"
#include "scene/light/utility/LightSample.hpp"
#include "foundation/geometry/Transform.hpp"
#include "visuals/Color3.hpp"

namespace toxico {
    struct LightBase {
        LightProperties properties;
        Transform transform;

        /**
         * @brief Constructor.
         * 
         * @param properties The properties of this light.
         */
        LightBase(const LightProperties& properties);

        /**
         * @brief Constructor.
         */
        LightBase() = default;

        /**
         * @brief Gets a sample of this light at a given point.
         * 
         * @param position The world position the light is being sampled at.
         * @return A sample of the light at this position.
         */
        virtual LightSample sample(const Vector3& position) const noexcept = 0;

        /**
         * @brief Destructor.
         */
        virtual ~LightBase() = default;
    };
}
