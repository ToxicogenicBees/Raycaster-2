/*
    SlotArray.hpp

    Declaration of a handle/slot buffer for run-time resource management.
*/

#pragma once

#include "foundation/concepts/HandleType.hpp"
#include <cstdint>
#include <vector>
#include <memory>
#include <utility>

namespace toxico {
    template<typename T, HandleType H>
    class SlotArray {
    public:
        using index_type = H::index_type;

        /**
         * @brief Constructor.
         */
        SlotArray() = default;

        /**
         * @brief Inserts a value into the array.
         * 
         * @param value The value being inserted.
         */
        H insert(const T& value);

        /**
         * @brief Inserts a value into the array.
         * 
         * @param value The value being inserted.
         */
        H insert(std::unique_ptr<T> value);

        /**
         * @brief Emplaces a value into the array.
         * 
         * @param args The constructor arguments for the value being inserted.
         */
        template<typename... Args>
        H emplace(Args&& ...args);

        /**
         * @brief Erases an item from the array.
         * 
         * @param handle The handle for the item being erased.
         */
        void erase(H handle);

        /**
         * @brief Resolve a handle.
         * 
         * @param handle The handle being resolved.
         * @return The resolved pointer.
         */
        const T* resolve(H handle) const;
        
        /**
         * @brief Resolve a handle.
         * 
         * @param handle The handle being resolved.
         * @return The resolved pointer.
         */
        T* resolve(H handle);

        /**
         * @brief Gets if the provided handle is valid.
         * 
         * @return If the handle is valid.
         */
        bool isValid(H handle) const;

    private:
        struct Slot {
            std::unique_ptr<T> object = nullptr;
            index_type generation = 0;
        };
        
        std::vector<Slot> slots_;
        std::vector<index_type> free_list_;
    };
}

#include "foundation/containers/SlotArray.tpp"
