/*
    ThreadPool.hpp

    Declaration of a thread pool object.
*/

#pragma once

#include "foundation/containers/OwningVector.hpp"
#include "foundation/threading/Fence.hpp"
#include "rendering/scheduling/threading/WorkerThread.hpp"
#include "rendering/scheduling/JobQueue.hpp"
#include "rendering/scheduling/JobHandle.hpp"

namespace toxico {
    class ThreadPool {
    private:
        const std::size_t THREAD_COUNT_;

        JobQueue queue_;
        OwningVector<WorkerThread> threads_;

    public:
        /**
         * @brief Constructor.
         * 
         * @param threads The number of threads in the pool.
         */
        ThreadPool(std::size_t threads = 0);

        /**
         * @brief Copy operations (deleted).
         */
        ThreadPool(const ThreadPool&) = delete;
        ThreadPool& operator=(const ThreadPool&) = delete;

        /**
         * @brief Move operations (deleted).
         */
        ThreadPool(ThreadPool&&) noexcept = delete;
        ThreadPool& operator=(ThreadPool&&) noexcept = delete;

        /**
         * @brief Submit a job to the pool.
         * 
         * @param task The task being submitted.
         * @return A handle for the submitted job.
         */
        JobHandle submit(std::function<void()> task);

        /**
         * @brief Gets the number of threads in the pool.
         * 
         * @return The number of threads in the pool.
         */
        std::size_t threads() const;
    };
}
