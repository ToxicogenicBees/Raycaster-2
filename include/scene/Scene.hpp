/*
    Scene.hpp

    Declaration of a scene of objects, lights, and geometries.
*/

#pragma once

#include "rendering/material/utility/MaterialHandle.hpp"
#include "scene/geometry/utility/GeometryHandle.hpp"
#include "scene/object/utility/ObjectHandle.hpp"
#include "scene/light/utility/LightHandle.hpp"
#include "foundation/containers/Registry.hpp"
#include "rendering/material/Material.hpp"
#include "scene/geometry/interfaces/IGeometry.hpp"
#include "scene/light/AmbientLight.hpp"
#include "scene/light/LightBase.hpp"
#include "scene/object/Object.hpp"
#include "scene/query/SurfaceInteraction.hpp"
#include <optional>

namespace toxico {
    struct Scene {
        Registry<IGeometry> geometries;
        Registry<Material> materials;
        Registry<LightBase> lights;
        Registry<Object> objects;
        AmbientLight ambience;

        /**
         * @brief Gets the closest intersection between this scene and a ray.
         * 
         * @param ray A ray in world coordinates.
         * @param t_min The minimum time traveled along the ray.
         * @param t_max The maxium time traveled along the ray.
         * @return The result of the intersection, or std::nullopt if no intersection occured.
         */
        std::optional<SurfaceInteraction> intersect(const Ray3& ray, fp_type t_min, fp_type t_max) const;

        /**
         * @brief Gets the closest intersection between this scene and a ray.
         * 
         * @param ray A ray in world coordinates.
         * @return The result of the intersection, or std::nullopt if no intersection occured.
         */
        std::optional<SurfaceInteraction> intersect(const Ray3& ray) const;
    };
}
