/*
    Scene.hpp

    Declaration of a scene of objects, lights, and geometries.
*/

#pragma once

#include "scene/geometry/utility/GeometryPrimitives.hpp"
#include "scene/geometry/utility/GeometryHandle.hpp"
#include "scene/geometry/GeometryRegistry.hpp"
#include "scene/query/SceneIntersection.hpp"
#include "foundation/containers/OwningVector.hpp"
#include "scene/object/Object.hpp"
#include <optional>
#include <concepts>
#include <vector>

namespace toxico {
    class Scene {
    private:
        OwningVector<Object> objects_;
        GeometryRegistry geometries_;

    public:
        /**
         * @brief Creates a geometry and adds it to the scene.
         * 
         * @param args The constructor arguments for this geometry.
         * @return A handle to this geometry.
         */
        template<std::derived_from<IGeometry> Geometry, typename... Ts>
        GeometryHandle createGeometry(Ts&& ...args);

        /**
         * @brief Gets a primitive geometry.
         * 
         * @param type The primitive geometry type.
         * @return A handle to this primitive geometry.
         */
        GeometryHandle getPrimitive(GeometryPrimitives type);

        /**
         * @brief Creates an object and adds it to the scene.
         * 
         * @param geometry The geometry type for this object
         * @return A reference to the created object.
         */
        Object& createObject(GeometryPrimitives geometry);
        Object& createObject(GeometryHandle geometry);

        /**
         * @brief Gets the closest intersection between this scene and a ray.
         * 
         * @param ray A ray in world coordinates.
         * @param t_min The minimum time traveled along the ray.
         * @param t_max The maxium time traveled along the ray.
         * @return The result of the intersection, or std::nullopt if no intersection occured.
         */
        std::optional<SceneIntersection> intersect(const Ray3& ray, fp_type t_min, fp_type t_max) const;

        /**
         * @brief Gets the closest intersection between this scene and a ray.
         * 
         * @param ray A ray in world coordinates.
         * @return The result of the intersection, or std::nullopt if no intersection occured.
         */
        std::optional<SceneIntersection> intersect(const Ray3& ray) const;
    };
}

#include "scene/Scene.tpp"
