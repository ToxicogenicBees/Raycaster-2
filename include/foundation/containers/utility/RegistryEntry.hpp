/*
    RegistryEntry.hpp

    Declaration of a dense entry for a registry.
*/

#pragma once

#include "foundation/containers/utility/RegistryHandle.hpp"
#include <memory>

namespace toxico {
    template<typename T, typename Index>
    struct RegistryEntry {
        std::unique_ptr<T> item;
        RegistryHandle<Index, Index, T> handle;
    };
}
