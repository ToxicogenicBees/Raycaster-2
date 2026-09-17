/*
    LightBase.hpp

    Declaration of an abstract light source.
*/

#pragma once

#include "scene/light/utility/LightSample.hpp"
#include "foundation/geometry/Transform.hpp"
#include "foundation/utility/fp_type.hpp"
#include "visuals/Color3.hpp"

namespace toxico {
    struct LightBase {
        Transform transform;
        Color3 color = Color3(1, 1, 1);
        fp_type intensity = 1.0;

        /**
         * @brief Constructor.
         * 
         * @param color The color of the light source.
         * @param intensity The intensity of the light source.
         */
        LightBase(const Color3& color, fp_type intensity);

        /**
         * @brief Constructor.
         * 
         * @param color The color of the light source.
         */
        LightBase(const Color3& color);

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
