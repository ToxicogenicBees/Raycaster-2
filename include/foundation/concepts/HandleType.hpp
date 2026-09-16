/*
    HandleType.hpp

    Declaration of a concept for a storage handle.
*/

#pragma once

#include <cstdint>
#include <concepts>

namespace toxico {
    template<typename T>
    concept HandleType = requires(const T& h) {
        // Must have an unsigned integer indexing type
        typename T::index_type;
        requires std::unsigned_integral<typename T::index_type>;

        // Must have an invalid index
        { T::invalid_index } -> std::convertible_to<typename T::index_type>;

        // Must provide index/generation access
        { h.index() } -> std::same_as<typename T::index_type>;
        { h.generation() } -> std::same_as<typename T::index_type>;

        // Must be constructable
        T{
            std::declval<typename T::index_type>(),
            std::declval<typename T::index_type>()
        };
    };
}
