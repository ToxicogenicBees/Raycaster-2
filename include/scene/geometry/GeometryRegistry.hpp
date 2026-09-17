/*
    GeometryRegistry.hpp

    Declaration of a registry for object geometry.
*/

#pragma once

#include "scene/geometry/utility/GeometryPrimitives.hpp"
#include "scene/geometry/utility/GeometryHandle.hpp"
#include "scene/geometry/interfaces/IGeometry.hpp"
#include "foundation/containers/SlotArray.hpp"
#include <unordered_map>

namespace toxico {
    class GeometryRegistry {
    private:
        std::unordered_map<GeometryPrimitives, GeometryHandle> primitives_;
        SlotArray<IGeometry, GeometryHandle> geometries_;

    public:
        /**
         * @brief Constructor.
         */
        GeometryRegistry();

        /**
         * @brief Creates a geometry.
         * 
         * @param args The constructor arguments for the geometry.
         */
        template<std::derived_from<IGeometry> Geometry, typename... Ts>
        GeometryHandle create(Ts&& ...args);

        /**
         * @brief Gets the desired primitive geometry.
         * 
         * @param type The desired primitive type.
         * @return A handle to the desired primitive geometry.
         */
        GeometryHandle getPrimitive(GeometryPrimitives type) const;

        /**
         * @brief Resolves a geometry handle.
         * 
         * @param handle The handle being resolved.
         * @return A pointer to the geometry, or nullptr if the handle was invalid.
         */
        const IGeometry* resolve(GeometryHandle handle) const noexcept;
        IGeometry* resolve(GeometryHandle handle) noexcept;

        /**
         * @brief Gets if a geometry handle is valid.
         * 
         * @param handle The handle being resolved.
         * @return If the handle is valid.
         */
        bool isValid(GeometryHandle handle) const noexcept;
    };
}

#include "scene/geometry/GeometryRegistry.tpp"
