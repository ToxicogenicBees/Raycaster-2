/*
    PhongProperties.cpp

    Implementation of a set of Phong shader properties.
*/

#include "rendering/shader/utility/PhongProperties.hpp"
#include <algorithm>

namespace toxico {
    fp_type f0(fp_type ior) {
        const fp_type x = (ior - 1.0) / (ior + 1.0);
        return x * x;
    }

    fp_type phongShininess(fp_type roughness) {
        const fp_type r = std::clamp(roughness, fp_type{0.001}, fp_type{1.0});
        return 2.0 / (r * r) - 2.0;
    }

    PhongProperties::PhongProperties(const MaterialProperties& sample) {
        // Calculate material properties
        const fp_type metallic = std::clamp(sample.metallic, fp_type{0}, fp_type{1});
        const fp_type ior = std::max(sample.ior, fp_type{1.0});
        const fp_type dielectric_f0 = f0(ior);

        // Phong diffuse
        this->diffuse = sample.base_color * (1.0 - metallic);
        
        // Phong ambience
        this->ambient = this->diffuse;

        // Phong specular
        this->specular =
            Color3(1, 1, 1) * (dielectric_f0 * (1.0 - metallic))
            + sample.base_color * metallic;

        // Phong shininess
        const fp_type roughness = std::clamp(sample.roughness, fp_type{0.001}, fp_type{1.0});
        this->shininess = phongShininess(roughness);
    }
}
