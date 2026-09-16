/*
    OwningVector.hpp

    Declaration of a vector holding polymorphic objects.
*/

#pragma once

#include "foundation/containers/iterators/OwningVectorIterator.hpp"
#include <type_traits>
#include <vector>
#include <memory>

namespace toxico {
    template<typename Base>
    class OwningVector {
    private:
        std::vector<std::unique_ptr<Base>> data_;

    public:
        using const_iterator = ConstOwningVectorIterator<Base>;
        using iterator = OwningVectorIterator<Base>;

        /**
         * @brief Inserts an item into the vector.
         * 
         * @param item The item being inserted.
         */
        template<std::derived_from<Base> T = Base>
        void push_back(std::unique_ptr<T> item);
        template<std::derived_from<Base> T = Base>
        void push_back(const T& item);

        /**
         * @brief Emplaces an item into the vector.
         * 
         * @param args The constructor arguments for the item being emplaced.
         * @return A reference to the emplaced item.
         */
        template<std::derived_from<Base> T = Base, typename... Args>
        T& emplace_back(Args&& ...args);

        /**
         * @brief Inserts an item into the vector.
         * 
         * @param pos An iterator at the desired insertion position.
         * @param value The value being inserted.
         */
        template<std::derived_from<Base> T = Base>
        iterator insert(const_iterator pos, std::unique_ptr<T> value);
        template<std::derived_from<Base> T = Base>
        iterator insert(const_iterator pos, const T& value);

        /**
         * @brief Erases an item from the vector.
         * 
         * @param pos The position being erased.
         * @return The iterator just after the removed element.
         */
        iterator erase(const_iterator pos);

        /**
         * @brief Erases a range from the vector.
         * 
         * @param first The beginning of the range.
         * @param last The end of the range.
         * @return The iterator just after the last removed element.
         */
        iterator erase(const_iterator first, const_iterator last);

        /**
         * @brief Pops the last element from the vector.
         */
        void pop_back() noexcept;

        /**
         * @brief Gets the item at an index, as a specific type.
         * 
         * @param index The desired vector index.
         * @return The item of that type.
         * 
         * Throws an error if the index is out of bounds.
         */
        template<std::derived_from<Base> T>
        const T& getAs(std::size_t index) const;
        template<std::derived_from<Base> T>
        T& getAs(std::size_t index);

        /**
         * @brief Gets the item at an index, as a specific type.
         * 
         * @param index The desired vector index.
         * @return The item of that type.
         * 
         * Throws an error if the index is out of bounds.
         */
        const Base& at(std::size_t index) const;
        Base& at(std::size_t index);

        /**
         * @brief Gets the item at an index, as a specific type.
         * 
         * @param index The desired vector index.
         * @return The item of that type.
         */
        const Base& operator[](std::size_t index) const;
        Base& operator[](std::size_t index);

        /**
         * @brief Gets the item at the front of the vector.
         * 
         * @return The item at the front of the vector.
         * 
         * Throws an exception if there are no items in the vector.
         * Throws an exception if the cast is bad.
         */
        template<std::derived_from<Base> T>
        const T& getFrontAs() const;
        template<std::derived_from<Base> T>
        T& getFrontAs();

        /**
         * @brief Gets the item at the front of the vector.
         * 
         * @return The item at the front of the vector.
         * 
         * Throws an exception if there are no items in the vector.
         * Throws an exception if the cast is bad.
         */
        const Base& front() const;
        Base& front();

        /**
         * @brief Gets the item at the back of the vector.
         * 
         * @return The item at the back of the vector.
         * 
         * Throws an exception if there are no items in the vector.
         * Throws an exception if the cast is bad.
         */
        template<std::derived_from<Base> T>
        const T& getBackAs() const;
        template<std::derived_from<Base> T>
        T& getBackAs();

        /**
         * @brief Gets the item at the back of the vector.
         * 
         * @return The item at the back of the vector.
         * 
         * Throws an exception if there are no items in the vector.
         * Throws an exception if the cast is bad.
         */
        const Base& back() const;
        Base& back();

        /**
         * @brief Resizes the vector.
         * 
         * @param size The desired size.
         */
        void resize(std::size_t size);

        /**
         * @brief Reserves space in the vector.
         * 
         * @param size The space being reserved.
         */
        void reserve(std::size_t size);

        /**
         * @brief Gets if the vector is empty.
         * 
         * @return If the vector is empty.
         */
        bool empty() const noexcept;

        /**
         * @brief Gets the capacity of the vector.
         * 
         * @return The capacity of the vector.
         */
        std::size_t capacity() const noexcept;

        /**
         * @brief Gets the size of the vector.
         * 
         * @return The size of the vector.
         */
        std::size_t size() const noexcept;

        /**
         * @brief Clears the vector.
         */
        void clear();

        /**
         * @brief Gets the desired iterator for this vector's unique_ptr items.
         * 
         * @return The desired iterator.
         */
        const_iterator cbegin() const noexcept;
        const_iterator begin() const noexcept;
        iterator begin() noexcept;
        const_iterator cend() const noexcept;
        const_iterator end() const noexcept;
        iterator end() noexcept;
    };
}

#include "foundation/containers/OwningVector.tpp"
