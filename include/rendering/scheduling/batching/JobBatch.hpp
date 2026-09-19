/*
    JobBatch.hpp

    Declaration of a job batch, a set of jobs related to each other.
*/

#pragma once

#include <functional>
#include <queue>

namespace toxico {
    class JobBatch {
    private:
        std::queue<std::function<void()>> tasks_;

    public:
        /**
         * @brief Constructor.
         */
        JobBatch() = default;

        /**
         * @brief Add a task to the batch.
         * 
         * @param job The job being added.
         */
        void push(std::function<void()> task) noexcept;

        /**
         * @brief Gets the next job in the batch.
         * 
         * @return The next job in the batch.
         */
        std::function<void()> pop();

        /**
         * @brief Gets if the job batch is empty.
         * 
         * @return If the batch is empty.
         */
        bool empty() const noexcept;

        /**
         * @brief Gets the number of batched jobs.
         * 
         * @return The number of batched jobs.
         */
        std::size_t size() const noexcept;
    };
}
