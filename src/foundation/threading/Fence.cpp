/*
    Fence.cpp

    Implementation of a thread-safe fence object.
*/

#include "foundation/threading/Fence.hpp"

namespace toxico {
    void Fence::add() {
        pending_.fetch_add(1, std::memory_order_acquire);
    }

    void Fence::complete() {
        if (pending_.fetch_sub(1, std::memory_order_release) == 1) {
            std::lock_guard lock(mutex_);
            condition_.notify_all();
        }
    }

    std::size_t Fence::pending() const {
        return pending_.load(std::memory_order_acquire);
    }

    void Fence::wait() const {
        std::unique_lock lock(mutex_);
        condition_.wait(lock, [this] {
            return pending_.load(std::memory_order_acquire) == 0;
        });
    }
}
