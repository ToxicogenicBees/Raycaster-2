/*
    GeometryHandle.hpp

    Declaration of a handle for geometries.
*/

#pragma once

#include "foundation/containers/utility/Handle.hpp"
#include "scene/geometry/interfaces/IGeometry.hpp"
#include <cstdint>

namespace toxico {
    using GeometryHandle = Handle<uint32_t, IGeometry>;
}
