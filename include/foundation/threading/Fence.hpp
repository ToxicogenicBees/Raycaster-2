/*
    Fence.hpp

    Declaration of a thread-safe fence object.
*/

#pragma once

#include <condition_variable>
#include <cstdint>
#include <atomic>
#include <mutex>

namespace toxico {
    class Fence {
    private:
        std::atomic<std::size_t> pending_{0};
        mutable std::condition_variable condition_;
        mutable std::mutex mutex_;

    public:
        /**
         * @brief Constructor.
         */
        Fence() = default;

        /**
         * @brief Copy operations (deleted).
         */
        Fence(const Fence&) = delete;
        Fence& operator=(const Fence&) = delete;

        /**
         * @brief Move operations (deleted).
         */
        Fence(Fence&&) noexcept = delete;
        Fence& operator=(Fence&&) noexcept = delete;

        /**
         * @brief Adds an outstanding request to the fence.
         */
        void add();

        /**
         * @brief Removes an outstanding request from the fence.
         */
        void complete();

        /**
         * @brief Gets the number of outstanding requests.
         * 
         * @return The number of outstanding requests.
         */
        std::size_t pending() const;

        /**
         * @brief Yields until all outstanding requests are completed.
         */
        void wait() const;
    };
}
