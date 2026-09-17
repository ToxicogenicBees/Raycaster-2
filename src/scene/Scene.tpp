/*
    Scene.tpp

    Template implementation of a scene of objects, lights, and geometries.
*/

#include <utility>

namespace toxico {
    template<std::derived_from<IGeometry> Geometry, typename... Ts>
    GeometryHandle Scene::createGeometry(Ts&& ...args) {
        return geometries_.create(std::forward<Ts>(args)...);
    }
}
