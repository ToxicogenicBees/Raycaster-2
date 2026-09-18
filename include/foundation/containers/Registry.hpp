/*
    Registry.hpp

    Declaration of a handle-indexed, dense-storage registery.
*/

#pragma once

#include "foundation/containers/iterators/RegistryIterator.hpp"
#include "foundation/containers/utility/RegistryHandle.hpp"
#include "foundation/containers/utility/RegistryEntry.hpp"
#include "foundation/containers/DenseVector.hpp"
#include "foundation/containers/SlotArray.hpp"
#include "foundation/concepts/RegistryItem.hpp"
#include <cstdint>

namespace toxico {
    template<typename Base, typename Index = uint32_t>
    class Registry {
    public:
        using value_type = Base;
        using index_type = Index;
        using handle_type = RegistryHandle<index_type, index_type, Base>;

        using const_iterator = ConstRegistryIterator<value_type, index_type>;
        using iterator = RegistryIterator<value_type, index_type>;

        /**
         * @brief Inserts an item into the registry.
         * 
         * @param item The item being inserted into the registry.
         * @return A handle to the inserted item.
         */
        template<typename Item = value_type>
        requires RegistryItem<Item, Base>
        handle_type insert(std::unique_ptr<Item> item);
        template<typename Item = value_type>
        requires RegistryItem<Item, Base>
        handle_type insert(const Item& item);

        /**
         * @brief Emplaces an item into the registry.
         * 
         * @param args The constructor arguments for the emplaced item.
         * @return A handle to the emplaced item.
         */
        template<typename Item = value_type, typename... Ts>
        requires RegistryItem<Item, Base>
        handle_type emplace(Ts&& ...args);

        /**
         * @brief Removes an item from the registry.
         * 
         * @param handle The handle to the item being removed.
         */
        void remove(handle_type handle) noexcept;

        /**
         * @brief Resolves a handle.
         * 
         * @param handle The handle being resolved.
         * @return A pointer to the resolved item, or nullptr if the handle was invalid.
         */
        template<typename Item = value_type>
        requires RegistryItem<Item, Base>
        const value_type* resolve(handle_type handle) const noexcept;
        template<typename Item = value_type>
        requires RegistryItem<Item, Base>
        value_type* resolve(handle_type handle) noexcept;

        /**
         * @brief Gets if a handle is valid.
         * 
         * @param handle The handle being validated.
         * @return If the handle is valid.
         */
        bool isValid(handle_type handle) const noexcept;

        /**
         * @brief Gets the desired iterator for this registry's items.
         * 
         * @return The desired iterator.
         */
        const_iterator cbegin() const noexcept;
        const_iterator begin() const noexcept;
        iterator begin() noexcept;
        const_iterator cend() const noexcept;
        const_iterator end() const noexcept;
        iterator end() noexcept;

    private:
        DenseVector<RegistryEntry<value_type, index_type>> dense_;
        SlotArray<index_type, handle_type> sparse_;
    };
}

#include "foundation/containers/Registry.tpp"
