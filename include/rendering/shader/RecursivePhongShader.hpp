/*
    RecursivePhongShader.hpp

    Declaration of a Phong shader.
*/

#pragma once

#include "rendering/shader/PhongShader.hpp"
#include "tracing/utility/SceneTrace.hpp"
#include "foundation/math/Ray.hpp"
#include "visuals/Color3.hpp"
#include "scene/Scene.hpp"
#include <cstdint>

namespace toxico {
    class RecursivePhongShader {
    private:
        static constexpr uint8_t MAX_DEPTH_ = 20;

        PhongShader phong_shader_;

        /**
         * @brief Runs a recursive shading calculation.
         * 
         * @param ray The ray being followed.
         * @param scene The scene the ray is traveling through.
         * @param background The desired background color.
         * @param depth The depth of the search
         * @param throughput The throughput of this trace.
         * @return The resulting color this ray's observer would see.
         */
        Color3 shade_(const Ray3& ray, const Scene& scene, const Color3& background, uint8_t depth, const Color3& throughput) const noexcept;

    public:
        /**
         * @brief Calculates the color for a ray traveling through a scene.
         * 
         * @param ray The ray being followed.
         * @param scene The scene the ray is traveling through.
         * @param background The desired background color.
         * @return The resulting color this ray's observer would see.
         */
        Color3 shade(const Ray3& ray, const Scene& scene, const Color3& background) const noexcept;
    };
}
