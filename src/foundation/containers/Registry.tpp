/*
    Registry.tpp

    Implementation of a handle-indexed, dense-storage registery.
*/

namespace toxico {
    template<typename Base, typename Index>
    template<typename Item>
    requires RegistryItem<Item, Base>
    typename Registry<Base, Index>::handle_type Registry<Base, Index>::insert(std::unique_ptr<Item> item) {
        // Create a new sparse entry
        const auto index = dense_.size();
        const auto handle = sparse_.insert(index);

        // Create a new dense entry
        dense_.push_back({
            std::move(item),
            handle
        });

        // Return the sparse handle
        return handle;
    }

    template<typename Base, typename Index>
    template<typename Item>
    requires RegistryItem<Item, Base>
    typename Registry<Base, Index>::handle_type Registry<Base, Index>::insert(const Item& item) {
        // Create a new sparse entry
        const auto index = dense_.size();
        const auto handle = sparse_.insert(index);

        // Create a new dense entry
        dense_.push_back({
            std::make_unique<Item>(item),
            handle
        });

        // Return the sparse handle
        return handle;
    }

    template<typename Base, typename Index>
    template<typename Item, typename... Ts>
    requires RegistryItem<Item, Base>
    std::pair<typename Registry<Base, Index>::handle_type, typename Registry<Base, Index>::value_type&> Registry<Base, Index>::emplace(Ts&& ...args) {
        // Create a new sparse entry
        const auto index = dense_.size();
        const auto handle = sparse_.insert(index);

        // Create a new dense entry
        dense_.push_back({
            std::make_unique<Item>(std::forward<Ts>(args)...),
            handle
        });

        // Return the sparse handle
        return {
            handle,
            *(dense_.back().item.get())
        };
    }

    template<typename Base, typename Index>
    void Registry<Base, Index>::remove(handle_type handle) noexcept {
        // Validate the handle
        if (!isValid(handle))
            return;

        // Fetch the dense index
        const auto* dense_index = sparse_.resolve(handle);

        // Remove the dense entry
        const auto result = dense_.erase(*dense_index);

        // Update meta-data
        if (result.moved) {
            auto& dense_entry = dense_.at(result.moved_to);
            auto* moved_index = sparse_.resolve(dense_entry.handle);
            *moved_index = result.moved_to;
        }
    }

    template<typename Base, typename Index>
    template<typename Item>
    requires RegistryItem<Item, Base>
    const typename Registry<Base, Index>::value_type* Registry<Base, Index>::resolve(handle_type handle) const noexcept {
        // Validate the handle
        if (!isValid(handle))
            return nullptr;

        // Fetch the dense index
        const auto* dense_index = sparse_.resolve(handle);

        // Fetch the dense item
        const auto& entry = dense_.at(*dense_index);
        return entry.item.get();
    }

    template<typename Base, typename Index>
    template<typename Item>
    requires RegistryItem<Item, Base>
    typename Registry<Base, Index>::value_type* Registry<Base, Index>::resolve(handle_type handle) noexcept {
        // Validate the handle
        if (!isValid(handle))
            return nullptr;

        // Fetch the dense index
        const auto* dense_index = sparse_.resolve(handle);

        // Fetch the dense item
        auto& entry = dense_.at(*dense_index);
        return entry.item.get();
    }

    template<typename Base, typename Index>
    bool Registry<Base, Index>::isValid(handle_type handle) const noexcept {
        return sparse_.isValid(handle);
    }

    template<typename Base, typename Index>
    typename Registry<Base, Index>::const_iterator Registry<Base, Index>::cbegin() const noexcept {
        return const_iterator(dense_.cbegin());
    }

    template<typename Base, typename Index>
    typename Registry<Base, Index>::const_iterator Registry<Base, Index>::begin() const noexcept {
        return const_iterator(dense_.begin());
    }

    template<typename Base, typename Index>
    typename Registry<Base, Index>::iterator Registry<Base, Index>::begin() noexcept {
        return iterator(dense_.begin());
    }

    template<typename Base, typename Index>
    typename Registry<Base, Index>::const_iterator Registry<Base, Index>::cend() const noexcept {
        return const_iterator(dense_.cend());
    }

    template<typename Base, typename Index>
    typename Registry<Base, Index>::const_iterator Registry<Base, Index>::end() const noexcept {
        return const_iterator(dense_.end());
    }

    template<typename Base, typename Index>
    typename Registry<Base, Index>::iterator Registry<Base, Index>::end() noexcept {
        return iterator(dense_.end());
    }
}
