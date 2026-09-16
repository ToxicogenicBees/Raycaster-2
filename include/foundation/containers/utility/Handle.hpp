/*
    Handle.hpp

    Declaration of a storage handle.
*/

#pragma once

#include <concepts>
#include <limits>

namespace toxico {
    template<std::unsigned_integral Index, typename DataType>
    class Handle {
    public:
        using index_type = Index;
        static constexpr index_type invalid_index = std::numeric_limits<index_type>::max();

        /**
         * @brief Constructor.
         * 
         * @param index The index of this id.
         * @param generation The generation of this id.
         */
        Handle(Index index, Index generation) noexcept;

        /**
         * @brief Constructor.
         */
        Handle() noexcept = default;

        /**
         * @brief Compares two entity ids.
         * 
         * @return If the two ids are the same.
         */
        bool operator==(Handle other) const noexcept;

        /**
         * @brief Gets the index of this id.
         * 
         * @return The index of this id.
         */
        Index index() const noexcept;

        /**
         * @brief Gets the generation of this id.
         * 
         * @return The generation of this id.
         */
        Index generation() const noexcept;

    private:
        Index index_ = invalid_index;
        Index generation_ = invalid_index;
    };
}

#include "foundation/containers/utility/Handle.tpp"
