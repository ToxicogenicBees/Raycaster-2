/*
    MaterialHandle.hpp

    Declaration of a handle for materials.
*/

#pragma once

#include "scene/material/Material.hpp"
#include "foundation/containers/Registry.hpp"
#include <cstdint>

namespace toxico {
    using MaterialHandle = Registry<Material>::handle_type;
}
