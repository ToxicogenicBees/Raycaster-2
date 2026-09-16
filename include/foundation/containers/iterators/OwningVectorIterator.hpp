/*
    OwningVectorIterator.hpp

    Declaration of an iterator for an owning vector.
*/

#pragma once

#include <type_traits>
#include <vector>
#include <memory>

namespace toxico {
    template<bool Const, typename Base>
    class OwningVectorIterator_ {
    public:
        using raw_storage_type = std::vector<std::unique_ptr<Base>>;
        using raw_iterator_type = std::conditional_t<Const, typename raw_storage_type::const_iterator, typename raw_storage_type::iterator>;
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = Base;
        using difference_type   = std::ptrdiff_t;
        using pointer           = std::conditional_t<Const, const Base*, Base*>;
        using reference         = std::conditional_t<Const, const Base&, Base&>;

        /**
         * @brief Constructor.
         * 
         * @param current An iterator for the owning vector's data.
         */
        OwningVectorIterator_(raw_iterator_type current) noexcept;

        /**
         * @brief Constructor.
         * 
         * @param other An iterator being constructed into to a const iterator.
         */
        template<bool OtherConst>
            requires (Const || !OtherConst)
        OwningVectorIterator_(const OwningVectorIterator_<OtherConst, Base>& other) noexcept;

        /**
         * @brief Comparison operators.
         * 
         * @param other Another iterator.
         * @return The result of the comparisons
         */
        bool operator==(const OwningVectorIterator_& other) const noexcept;
        bool operator!=(const OwningVectorIterator_& other) const noexcept;
        bool operator<(const OwningVectorIterator_& other) const noexcept;
        bool operator<=(const OwningVectorIterator_& other) const noexcept;
        bool operator>(const OwningVectorIterator_& other) const noexcept;
        bool operator>=(const OwningVectorIterator_& other) const noexcept;

        /**
         * @brief Pre-increment/decrement operators.
         * 
         * @return A reference to the modified iterator.
         */
        OwningVectorIterator_& operator++() noexcept;
        OwningVectorIterator_& operator--() noexcept;

        /**
         * @brief Post-increment/decrement operators.
         * 
         * @return A copy of the iterator.
         */
        OwningVectorIterator_ operator++(int) noexcept;
        OwningVectorIterator_ operator--(int) noexcept;

        /**
         * @brief Offset operators.
         * 
         * @param n The desired offset.
         * @return The modified iterator.
         */
        OwningVectorIterator_ operator+(std::ptrdiff_t n) const noexcept;
        OwningVectorIterator_ operator-(std::ptrdiff_t n) const noexcept;

        /**
         * @brief Offset + assignment operators.
         * 
         * @param n The desired offset.
         * @return A reference to the modified iterator.
         */
        OwningVectorIterator_& operator+=(std::ptrdiff_t n) noexcept;
        OwningVectorIterator_& operator-=(std::ptrdiff_t n) noexcept;

        /**
         * @brief Offset operator.
         * 
         * @param other Another pointer.
         * @return The difference between the pointers.
         */
        std::ptrdiff_t operator-(const OwningVectorIterator_& other) const noexcept;

        /**
         * @brief Dereference operator.
         * 
         * @return A reference to the object at this iterator.
         */
        reference operator*() const;

        /**
         * @brief Structure pointer dereference operator.
         * 
         * @return A reference to the object at this iterator.
         */
        pointer operator->() const;

        /**
         * @brief Indexing operator.
         * 
         * @param n The desired offset into the iterator.
         * @return The item at the desired value.
         */
        reference operator[](std::ptrdiff_t n) const;

        /**
         * @brief Gets the internally stored storage iterator.
         * 
         * @return The internally stored storage iterator.
         */
        raw_iterator_type get() const noexcept;

    private:
        raw_iterator_type current_;
    };

    template<typename Base>
    using ConstOwningVectorIterator = OwningVectorIterator_<true, Base>;
    template<typename Base>
    using OwningVectorIterator = OwningVectorIterator_<false, Base>;
}

#include "foundation/containers/iterators/OwningVectorIterator.tpp"
