/*
    RegistryHandle.tpp

    Template implementation of a registry storage handle.
*/

namespace toxico {
    template<std::unsigned_integral Index, typename DenseIndex, typename DataType>
    RegistryHandle<Index, DenseIndex, DataType>::RegistryHandle(Index index, Index generation) noexcept
        : index_(index),
          generation_(generation)
    {}

    template<std::unsigned_integral Index, typename DenseIndex, typename DataType>
    bool RegistryHandle<Index, DenseIndex, DataType>::operator==(RegistryHandle other) const noexcept {
        return index_ == other.index_ && generation_ == other.generation_;
    }

    template<std::unsigned_integral Index, typename DenseIndex, typename DataType>
    Index RegistryHandle<Index, DenseIndex, DataType>::index() const noexcept {
        return index_;
    }

    template<std::unsigned_integral Index, typename DenseIndex, typename DataType>
    Index RegistryHandle<Index, DenseIndex, DataType>::generation() const noexcept {
        return generation_;
    }
}
