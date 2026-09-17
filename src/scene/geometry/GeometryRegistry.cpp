/*
    GeometryRegistry.hpp

    Declaration of a registry for object geometry.
*/

#include "scene/geometry/GeometryRegistry.hpp"
#include "scene/geometry/SphereGeometry.hpp"
#include "scene/geometry/PlaneGeometry.hpp"

namespace toxico {
    GeometryRegistry::GeometryRegistry() {
        primitives_.insert({GeometryPrimitives::Sphere, create<SphereGeometry>()});
        primitives_.insert({GeometryPrimitives::Plane, create<PlaneGeometry>()});
    }

    GeometryHandle GeometryRegistry::getPrimitive(GeometryPrimitives type) const {
        return primitives_.at(type);
    }

    const IGeometry* GeometryRegistry::resolve(GeometryHandle handle) const noexcept {
        return geometries_.resolve(handle);
    }

    IGeometry* GeometryRegistry::resolve(GeometryHandle handle) noexcept {
        return geometries_.resolve(handle);
    }

    bool GeometryRegistry::isValid(GeometryHandle handle) const noexcept {
        return geometries_.isValid(handle);
    }
}
