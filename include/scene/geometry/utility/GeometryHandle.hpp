/*
    GeometryHandle.hpp

    Declaration of a handle for geometries.
*/

#pragma once

#include "scene/geometry/interfaces/IGeometry.hpp"
#include "foundation/containers/Registry.hpp"
#include <cstdint>

namespace toxico {
    using GeometryHandle = Registry<IGeometry>::handle_type;
}
