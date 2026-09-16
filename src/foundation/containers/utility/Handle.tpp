/*
    Handle.tpp

    Template implementation of a storage handle.
*/

namespace toxico {
    template<std::unsigned_integral Index, typename DataType>
    Handle<Index, DataType>::Handle(Index index, Index generation) noexcept
        : index_(index),
          generation_(generation)
    {}

    template<std::unsigned_integral Index, typename DataType>
    bool Handle<Index, DataType>::operator==(Handle<Index, DataType> other) const noexcept {
        return index_ == other.index_ && generation_ == other.generation_;
    }

    template<std::unsigned_integral Index, typename DataType>
    Index Handle<Index, DataType>::index() const noexcept {
        return index_;
    }

    template<std::unsigned_integral Index, typename DataType>
    Index Handle<Index, DataType>::generation() const noexcept {
        return generation_;
    }
}
