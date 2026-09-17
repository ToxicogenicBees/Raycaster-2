/*
    GeometryRegistry.tpp

    Template implementation of a registry for object geometry.
*/

#include <utility>
#include <memory>

namespace toxico {
    template<std::derived_from<IGeometry> Geometry, typename... Ts>
    GeometryHandle GeometryRegistry::create(Ts&& ...args) {
        return geometries_.insert(std::make_unique<Geometry>(std::forward<Ts>(args)...));
    }
}
