/*
    Spotlight.hpp

    Declaration of a spotlight.
*/

#pragma once

#include "scene/light/LightBase.hpp"
#include "scene/light/utility/LightProperties.hpp"
#include "scene/light/utility/LightSample.hpp"
#include "foundation/utility/fp_type.hpp"
#include "foundation/math/Vector.hpp"

namespace toxico {
    struct Spotlight final : LightBase {
    private:
        fp_type inner_angle;
        fp_type outer_angle;

    public:
        /**
         * @brief Constructor.
         * 
         * @param inner_angle The angle of the light's inner cone (0 to 180 degrees).
         * @param outer_angle The angle of the light's outer cone (0 to 180 degrees).
         * @param properties The properties of this light.
         */
        Spotlight(fp_type inner_angle, fp_type outer_angle, const LightProperties& properties);

        /**
         * @brief Constructor.
         * 
         * @param cone_angle The angle of the cone, in radians (0 to 180 degrees).
         * @param properties The properties of this light.
         */
        Spotlight(fp_type cone_angle, const LightProperties& properties);

        /**
         * @brief Constructor.
         * 
         * @param inner_angle The angle of the light's inner cone (0 to 180 degrees).
         * @param outer_angle The angle of the light's outer cone (0 to 180 degrees).
         */
        Spotlight(fp_type inner_angle, fp_type outer_angle);

        /**
         * @brief Constructor.
         * 
         * @param cone_angle The angle of the cone, in radians (0 to 180 degrees).
         */
        Spotlight(fp_type cone_angle);

        /**
         * @brief Gets a sample of this light at a given point.
         * 
         * @param position The world position the light is being sampled at.
         * @return A sample of the light at this position.
         */
        LightSample sample(const Vector3& position) const noexcept final;
    };
}
