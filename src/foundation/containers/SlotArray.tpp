/*
    SlotArray.tpp

    Template implementation of a handle/slot buffer for run-time resource management.
*/

#include <utility>

namespace toxico {
    template<typename T, HandleType H>
    H SlotArray<T, H>::insert(const T& value) {
        // Fetch a valid index
        index_type index = slots_.size();
        if (!free_list_.empty()) {
            index = free_list_.back();
            free_list_.pop_back();
        }

        // Add a new slot if needed
        if (index == slots_.size())
            slots_.push_back(Slot{});

        // Insert the new item
        auto& slot = slots_[index];
        slot.object = std::make_unique<T>(value);

        // Return a handle for this slot
        return H(
            index,
            slot.generation
        );
    }

    template<typename T, HandleType H>
    H SlotArray<T, H>::insert(std::unique_ptr<T> value) {
        // Fetch a valid index
        index_type index = slots_.size();
        if (!free_list_.empty()) {
            index = free_list_.back();
            free_list_.pop_back();
        }

        // Add a new slot if needed
        if (index == slots_.size())
            slots_.push_back(Slot{});

        // Insert the new item
        auto& slot = slots_[index];
        slot.object = std::move(value);

        // Return a handle for this slot
        return H(
            index,
            slot.generation
        );
    }

    template<typename T, HandleType H>
    template<typename... Args>
    H SlotArray<T, H>::emplace(Args&& ...args) {
        // Fetch a valid index
        index_type index = slots_.size();
        if (!free_list_.empty()) {
            index = free_list_.back();
            free_list_.pop_back();
        }

        // Add a new slot if needed
        if (index == slots_.size())
            slots_.push_back(Slot{});

        // Emplace the new item
        auto& slot = slots_[index];
        slot.object = std::make_unique<T>(std::forward<Args>(args)...);

        // Return a handle for this slot
        return H(
            index,
            slot.generation
        );
    }

    template<typename T, HandleType H>
    void SlotArray<T, H>::erase(H handle) {
        // Ignore invalid handles
        auto* object = resolve(handle);
        if (!object)
            return;

        // Fetch the slot being freed
        auto index = handle.index();
        auto& slot = slots_[index];

        // Increment slot generation
        ++(slot.generation);
        if (slot.generation == H::invalid_index) {
            // Overflow so generation remains valid
            ++slot.generation;
        }
        
        // Free slot memory
        if (slot.object)
            slot.object.reset();
        
        // Free index for future use
        free_list_.push_back(index);
    }

    template<typename T, HandleType H>
    const T* SlotArray<T, H>::resolve(H handle) const {
        // Handle is invalid
        if (handle.index() >= slots_.size() || handle.index() == H::invalid_index)
            return nullptr;

        // Fetch slot by handle index
        auto& slot = slots_[handle.index()];

        // Invalidate slots on generation mismatch
        if (slot.generation != handle.generation())
            return nullptr;

        // Return the value
        return slot.object.get();
    }

    template<typename T, HandleType H>
    T* SlotArray<T, H>::resolve(H handle) {
        return const_cast<T*>(
            std::as_const(*this).resolve(handle)
        );
    }

    template<typename T, HandleType H>
    bool SlotArray<T, H>::isValid(H handle) const {
        return resolve(handle) != nullptr;
    }
}
