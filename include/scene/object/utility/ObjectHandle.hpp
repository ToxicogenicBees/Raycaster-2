/*
    ObjectHandle.hpp

    Declaration of a handle for objects.
*/

#pragma once

#include "foundation/containers/Registry.hpp"
#include "scene/object/Object.hpp"
#include <cstdint>

namespace toxico {
    using ObjectHandle = Registry<Object>::handle_type;
}
