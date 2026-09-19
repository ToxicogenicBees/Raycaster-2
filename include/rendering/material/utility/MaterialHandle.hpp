/*
    MaterialHandle.hpp

    Declaration of a handle for materials.
*/

#pragma once

#include "rendering/material/interfaces/IMaterial.hpp"
#include "foundation/containers/Registry.hpp"
#include <cstdint>

namespace toxico {
    using MaterialHandle = Registry<IMaterial>::handle_type;
}
