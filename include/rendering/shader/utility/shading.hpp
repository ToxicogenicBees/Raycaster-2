/*
    shading.hpp

    Declaration of a set of free functions to help in shading.
*/

#pragma once

#include "scene/light/utility/LightSample.hpp"
#include "tracing/utility/SceneTrace.hpp"
#include "foundation/math/Vector.hpp"
#include "scene/Scene.hpp"

namespace toxico::shading {
    /**
     * @brief Gets if a light casts a shadow on an object.
     * 
     * @param scene The scene containing the light.
     * @param light_sample The sampled light being checked.
     * @param trace The trace at the point shadow would be casted on.
     * @return If the light casts a shadow on the point.
     */
    bool castsShadow(const Scene& scene, const LightSample& light_sample, const SceneTrace& trace);

    /**
     * @brief Reflects a vector by a normal vector.
     * 
     * @param v The vector being reflected.
     * @param n The normal vector being reflected about.
     * @return The reflected vector.
     */
    Vector3 reflect(const Vector3 v, const Vector3 n);
}
