/*
    OwningVectorIterator.tpp

    Template implementation of an iterator for an owning vector.
*/

#pragma once

#include <type_traits>
#include <vector>
#include <memory>

namespace toxico {
    template<bool Const, typename Base>
    OwningVectorIterator_<Const, Base>::OwningVectorIterator_(raw_iterator_type current) noexcept
        : current_(current) {}

    template<bool Const, typename Base>
    template<bool OtherConst>
        requires (Const || !OtherConst)
    OwningVectorIterator_<Const, Base>::OwningVectorIterator_(const OwningVectorIterator_<OtherConst, Base>& other) noexcept
        : current_(other.get())
    {}

    template<bool Const, typename Base>
    bool OwningVectorIterator_<Const, Base>::operator==(const OwningVectorIterator_& other) const noexcept {
        return current_ == other.current_;
    }

    template<bool Const, typename Base>
    bool OwningVectorIterator_<Const, Base>::operator!=(const OwningVectorIterator_& other) const noexcept {
        return current_ != other.current_;
    }

    template<bool Const, typename Base>
    bool OwningVectorIterator_<Const, Base>::operator<(const OwningVectorIterator_& other) const noexcept {
        return current_ < other.current_;
    }

    template<bool Const, typename Base>
    bool OwningVectorIterator_<Const, Base>::operator<=(const OwningVectorIterator_& other) const noexcept {
        return current_ <= other.current_;
    }

    template<bool Const, typename Base>
    bool OwningVectorIterator_<Const, Base>::operator>(const OwningVectorIterator_& other) const noexcept {
        return current_ > other.current_;
    }

    template<bool Const, typename Base>
    bool OwningVectorIterator_<Const, Base>::operator>=(const OwningVectorIterator_& other) const noexcept {
        return current_ >= other.current_;
    }

    template<bool Const, typename Base>
    OwningVectorIterator_<Const, Base>& OwningVectorIterator_<Const, Base>::operator++() noexcept {
        ++current_;
        return *this;
    }

    template<bool Const, typename Base>
    OwningVectorIterator_<Const, Base>& OwningVectorIterator_<Const, Base>::operator--() noexcept {
        --current_;
        return *this;
    }

    template<bool Const, typename Base>
    OwningVectorIterator_<Const, Base> OwningVectorIterator_<Const, Base>::operator++(int) noexcept {
        auto copy = *this;
        ++current_;
        return copy;
    }

    template<bool Const, typename Base>
    OwningVectorIterator_<Const, Base> OwningVectorIterator_<Const, Base>::operator--(int) noexcept {
        auto copy = *this;
        --current_;
        return copy;
    }

    template<bool Const, typename Base>
    OwningVectorIterator_<Const, Base> OwningVectorIterator_<Const, Base>::operator+(std::ptrdiff_t n) const noexcept {
        return OwningVectorIterator_<Const, Base>(current_ + n);
    }

    template<bool Const, typename Base>
    OwningVectorIterator_<Const, Base> OwningVectorIterator_<Const, Base>::operator-(std::ptrdiff_t n) const noexcept {
        return OwningVectorIterator_<Const, Base>(current_ - n);
    }

    template<bool Const, typename Base>
    OwningVectorIterator_<Const, Base>& OwningVectorIterator_<Const, Base>::operator+=(std::ptrdiff_t n) noexcept {
        current_ += n;
        return *this;
    }

    template<bool Const, typename Base>
    OwningVectorIterator_<Const, Base>& OwningVectorIterator_<Const, Base>::operator-=(std::ptrdiff_t n) noexcept {
        current_ -= n;
        return *this;
    }
    
    template<bool Const, typename Base>
    std::ptrdiff_t OwningVectorIterator_<Const, Base>::operator-(const OwningVectorIterator_& other) const noexcept {
        return current_ - other.current_;
    }

    template<bool Const, typename Base>
    typename OwningVectorIterator_<Const, Base>::reference
    OwningVectorIterator_<Const, Base>::operator[](std::ptrdiff_t n) const {
        return *(current_[n]);
    }
    
    template<bool Const, typename Base>
    typename OwningVectorIterator_<Const, Base>::reference OwningVectorIterator_<Const, Base>::operator*() const {
        return *(current_->get());
    }
    
    template<bool Const, typename Base>
    typename OwningVectorIterator_<Const, Base>::pointer OwningVectorIterator_<Const, Base>::operator->() const {
        return std::addressof(operator*());
    }
    
    template<bool Const, typename Base>
    typename OwningVectorIterator_<Const, Base>::raw_iterator_type OwningVectorIterator_<Const, Base>::get() const noexcept {
        return current_;
    }
}

#include "foundation/containers/iterators/OwningVectorIterator.tpp"
