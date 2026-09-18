/*
    RegistryItem.hpp

    Declaration of a concept for a registry item.
*/

#pragma once

#include <concepts>

namespace toxico {
    template<typename Derived, typename Base>
    concept RegistryItem =
        std::same_as<Derived, Base> ||
        std::derived_from<Derived, Base>;
}
