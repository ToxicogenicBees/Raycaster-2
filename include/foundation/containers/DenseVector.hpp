/*
    DenseVector.hpp

    Declaration of a container with swap-and-pop erase semantics.
*/

#pragma once

#include "foundation/containers/utility/DenseErasure.hpp"
#include <iterator>
#include <cstddef>
#include <vector>
#include <optional>
#include <type_traits>

namespace toxico {
    template<typename T>
    requires std::is_move_assignable_v<T>
    class DenseVector {
    public:
        using value_type = T;
        using const_iterator = std::vector<value_type>::const_iterator;
        using iterator = std::vector<value_type>::iterator;

        /**
         * @brief Indexes the container.
         * 
         * @param index The index of the desired item.
         * @return The item at that index.
         */
        const T& operator[](std::size_t index) const;
        T& operator[](std::size_t index);

        /**
         * @brief Indexes the container.
         * 
         * @param index The index of the desired item.
         * @return The item at that index.
         * 
         * Throws an exception if the index is out of bounds.
         */
        const T& at(std::size_t index) const;
        T& at(std::size_t index);

        /**
         * @brief Gets the item in the front of the container.
         * 
         * @return The item in the front of the container.
         * 
         * Throws an exception if the container is empty.
         */
        const T& front() const;
        T& front();

        /**
         * @brief Gets the item in the back of the container.
         * 
         * @return The item in the back of the container.
         * 
         * Throws an exception if the container is empty.
         */
        const T& back() const;
        T& back();

        /**
         * @brief Gets the size of the container.
         * 
         * @return The size of the container.
         */
        std::size_t size() const noexcept;

        /**
         * @brief Gets if this container is empty.
         * 
         * @return If the container is empty.
         */
        bool empty() const noexcept;

        /**
         * @brief Reserves space in the container.
         * 
         * @param capacity The desired reserved capacity.
         */
        void reserve(std::size_t capacity);
        
        /**
         * @brief Emplaces an item into the back of the container.
         * 
         * @param args The constructor arguments for the item.
         */
        template<typename... Args>
        T& emplace_back(Args&&... args);

        /**
         * @brief Pushes an item into the back of the container.
         * 
         * @param value The value being pushed.
         */
        void push_back(const T& value);
        void push_back(T&& value);

        /**
         * @brief Removes the last item from the container.
         */
        void pop_back() noexcept;

        /**
         * @brief Erases an item from the container.
         * 
         * @param index The index being erased.
         * @return The result of this erasure.
         */
        DenseErasure erase(std::size_t index) noexcept;

        /**
         * @brief Clears the data in this container.
         */
        void clear() noexcept;

        /**
         * @brief Gets a pointer to this container's data.
         * 
         * @return A pointer to this container's data.
         */
        const T* data() const noexcept;
        T* data() noexcept;

        /**
         * @brief Gets the desired iterator for this grid's data.
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
        std::vector<value_type> data_;
    };
}

#include "foundation/containers/DenseVector.tpp"
