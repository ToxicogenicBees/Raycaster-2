/*
    Scene.hpp

    Declaration of a scene of objects, lights, geometries, and materials.
*/

#pragma once

#include "foundation/containers/Registry.hpp"
#include "scene/geometry/interfaces/IGeometry.hpp"
#include "rendering/material/Material.hpp"
#include "scene/light/LightBase.hpp"
#include "scene/object/Object.hpp"
#include "scene/light/AmbientLight.hpp"

namespace toxico {
    struct Scene {
        Registry<IGeometry> geometries;
        Registry<Material> materials;
        Registry<LightBase> lights;
        Registry<Object> objects;
        AmbientLight ambience;
    };
}
