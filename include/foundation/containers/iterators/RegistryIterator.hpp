/*
    RegistryIterator.hpp

    Declaration of an iterator for a registry.
*/

#pragma once

#include "foundation/containers/utility/RegistryEntry.hpp"
#include "foundation/containers/DenseVector.hpp"
#include <type_traits>
#include <memory>

namespace toxico {
    template<bool Const, typename T, typename Index>
    class RegistryIterator_ {
    public:
        using raw_storage_type = DenseVector<RegistryEntry<T, Index>>;
        using raw_iterator_type = std::conditional_t<Const, typename raw_storage_type::const_iterator, typename raw_storage_type::iterator>;
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = std::conditional_t<Const, const T*, T*>;
        using reference         = std::conditional_t<Const, const T&, T&>;

        /**
         * @brief Constructor.
         * 
         * @param current An iterator for the registry's data.
         */
        RegistryIterator_(raw_iterator_type current) noexcept;

        /**
         * @brief Constructor.
         * 
         * @param other An iterator being constructed into to a const iterator.
         */
        template<bool OtherConst>
            requires (Const || !OtherConst)
        RegistryIterator_(const RegistryIterator_<OtherConst, T, Index>& other) noexcept;

        /**
         * @brief Comparison operators.
         * 
         * @param other Another iterator.
         * @return The result of the comparisos.
         */
        bool operator==(const RegistryIterator_& other) const noexcept;
        bool operator!=(const RegistryIterator_& other) const noexcept;

        /**
         * @brief Pre-increment operator.
         * 
         * @return A reference to the modified iterator.
         */
        RegistryIterator_& operator++() noexcept;

        /**
         * @brief Post-increment operator.
         * 
         * @return A copy of the iterator.
         */
        RegistryIterator_ operator++(int) noexcept;

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
         * @brief Gets the internally stored storage iterator.
         * 
         * @return The internally stored storage iterator.
         */
        raw_iterator_type get() const noexcept;

    private:
        raw_iterator_type current_;
    };

    template<typename T, typename Index>
    using ConstRegistryIterator = RegistryIterator_<true, T, Index>;
    template<typename T, typename Index>
    using RegistryIterator = RegistryIterator_<false, T, Index>;
}

#include "foundation/containers/iterators/RegistryIterator.tpp"
