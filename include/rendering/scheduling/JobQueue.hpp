/*
    JobQueue.hpp

    Declaration of a thread-safe job queue.
*/

#pragma once

#include "rendering/scheduling/JobHandle.hpp"
#include "rendering/scheduling/Job.hpp"
#include <condition_variable>
#include <queue>
#include <mutex>
#include <optional>

namespace toxico {
    class JobQueue {
    private:
        mutable std::mutex mutex_;
        std::condition_variable_any condition_;
        std::queue<Job> jobs_;
        bool stopped_ = false;

    public:
        /**
         * @brief Constructor.
         */
        JobQueue() = default;

        /**
         * @brief Adds a task to the queue.
         * 
         * @param task The task being added.
         * @param on_complete An optional post-work task for this job.
         * @return A handle for the created job.
         */
        JobHandle push(std::function<void()> task, std::function<void()> on_complete = {});

        /**
         * @brief Waits for and then removes a job from the queue.
         * 
         * @param stop The requesting worker thread's stop token
         * @return The job popped from the queue.
         */
        std::optional<Job> pop(std::stop_token stop);
        
        /**
         * @brief Stops the queue.
         *        The queue will still process all remaining jobs.
         */
        void stop();

        /**
         * @brief Gets if the queue is stopped.
         * 
         * @return If the queue is stopped.
         */
        bool stopped() const;

        /**
         * @brief Gets the size of the queue.
         * 
         * @return The size of the queue.
         */
        std::size_t size() const;

        /**
         * @brief Gets if the queue is empty.
         * 
         * @return If the queue is empty.
         */
        bool empty() const;

        /**
         * @brief Destructor.
         */
        ~JobQueue();
    };
}
