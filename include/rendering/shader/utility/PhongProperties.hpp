/*
    PhongProperties.hpp

    Declaration of a set of Phong shader properties.
*/

#pragma once

#include "rendering/material/utility/MaterialProperties.hpp"
#include "foundation/utility/fp_type.hpp"
#include "visuals/Color3.hpp"

namespace toxico {
    struct PhongProperties {
        Color3 ambient;
        Color3 diffuse;
        Color3 specular;
        fp_type shininess;

        /**
         * @brief Constructor.
         * 
         * @param sample A material sample.
         */
        PhongProperties(const MaterialProperties& sample);

        /**
         * @brief Constructor.
         */
        PhongProperties() = default;
    };
}
