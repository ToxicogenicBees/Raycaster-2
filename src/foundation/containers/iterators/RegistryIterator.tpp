/*
    RegistryIterator.tpp

    Template implementation of an iterator for an owning vector.
*/

#pragma once

#include <type_traits>
#include <vector>
#include <memory>

namespace toxico {
    template<bool Const, typename T, typename Index>
    RegistryIterator_<Const, T, Index>::RegistryIterator_(raw_iterator_type current) noexcept
        : current_(current) {}

    template<bool Const, typename T, typename Index>
    template<bool OtherConst>
        requires (Const || !OtherConst)
    RegistryIterator_<Const, T, Index>::RegistryIterator_(const RegistryIterator_<OtherConst, T, Index>& other) noexcept
        : current_(other.get())
    {}

    template<bool Const, typename T, typename Index>
    bool RegistryIterator_<Const, T, Index>::operator==(const RegistryIterator_& other) const noexcept {
        return current_ == other.current_;
    }

    template<bool Const, typename T, typename Index>
    bool RegistryIterator_<Const, T, Index>::operator!=(const RegistryIterator_& other) const noexcept {
        return current_ != other.current_;
    }

    template<bool Const, typename T, typename Index>
    RegistryIterator_<Const, T, Index>& RegistryIterator_<Const, T, Index>::operator++() noexcept {
        ++current_;
        return *this;
    }

    template<bool Const, typename T, typename Index>
    RegistryIterator_<Const, T, Index> RegistryIterator_<Const, T, Index>::operator++(int) noexcept {
        auto copy = *this;
        ++current_;
        return copy;
    }
    
    template<bool Const, typename T, typename Index>
    typename RegistryIterator_<Const, T, Index>::reference RegistryIterator_<Const, T, Index>::operator*() const {
        return *(current_->item.get());
    }
    
    template<bool Const, typename T, typename Index>
    typename RegistryIterator_<Const, T, Index>::pointer RegistryIterator_<Const, T, Index>::operator->() const {
        return std::addressof(operator*());
    }
    
    template<bool Const, typename T, typename Index>
    typename RegistryIterator_<Const, T, Index>::raw_iterator_type RegistryIterator_<Const, T, Index>::get() const noexcept {
        return current_;
    }
}
