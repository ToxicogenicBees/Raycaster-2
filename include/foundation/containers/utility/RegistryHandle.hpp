/*
    RegistryHandle.hpp

    Declaration of a registry storage handle.
*/

#pragma once

#include <concepts>
#include <limits>

namespace toxico {
    template<std::unsigned_integral Index, typename DenseIndex, typename DataType>
    class RegistryHandle {
    public:
        using index_type = Index;
        using dense_index_type = DenseIndex;
        static constexpr index_type invalid_index = std::numeric_limits<index_type>::max();

        /**
         * @brief Constructor.
         * 
         * @param index The index of this id.
         * @param generation The generation of this id.
         */
        RegistryHandle(Index index, Index generation) noexcept;

        /**
         * @brief Constructor.
         */
        RegistryHandle() noexcept = default;

        /**
         * @brief Compares two entity ids.
         * 
         * @return If the two ids are the same.
         */
        bool operator==(RegistryHandle other) const noexcept;

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

#include "foundation/containers/utility/RegistryHandle.tpp"
