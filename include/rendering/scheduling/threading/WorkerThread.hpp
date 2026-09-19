/*
    WorkerThread.hpp

    Declaration of a working thread object.
*/

#pragma once

#include "rendering/scheduling/JobQueue.hpp"
#include <condition_variable>
#include <optional>
#include <thread>
#include <atomic>

namespace toxico {
    class WorkerThread {
    private:
        JobQueue& queue_;
        std::jthread thread_;

    public:
        /**
         * @brief Constructor.
         * 
         * @param queue The job queue used by this worker.
         */
        explicit WorkerThread(JobQueue& queue);

        /**
         * @brief Copy operations (deleted).
         */
        WorkerThread(const WorkerThread&) = delete;
        WorkerThread& operator=(const WorkerThread&) = delete;

        /**
         * @brief Move operations (deleted).
         */
        WorkerThread(WorkerThread&&) noexcept = delete;
        WorkerThread& operator=(WorkerThread&&) noexcept = delete;

        /**
         * @brief Requests for this worker to stop working.
         */
        void stop();

        /**
         * @brief Destructor.
         */
        ~WorkerThread();
    };
}
