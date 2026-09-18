/*
    LightHandle.hpp

    Declaration of a handle for lights.
*/

#pragma once

#include "foundation/containers/Registry.hpp"
#include "scene/light/LightBase.hpp"
#include <cstdint>

namespace toxico {
    using LightHandle = Registry<LightBase>::handle_type;
}
