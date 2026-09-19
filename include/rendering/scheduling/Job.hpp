/*
    Job.hpp

    Declaration of a job object.
*/

#pragma once

#include "rendering/scheduling/JobState.hpp"
#include "rendering/scheduling/JobHandle.hpp"
#include <functional>
#include <memory>

namespace toxico {
    class Job {
    private:
        std::shared_ptr<JobState> state_;
        std::function<void()> on_complete_;
        std::function<void()> task_;

    public:
        /**
         * @brief Constructor.
         * 
         * @param task The task this job is executing.
         * @param on_complete An optional post-work task for this job.
         */
        Job(std::function<void()> task, std::function<void()> on_complete = {});

        /**
         * @brief Copy constructor (deleted).
         */
        Job(const Job&) = delete;

        /**
         * @brief Copy assignment operator (deleted).
         */
        Job& operator=(const Job&) = delete;

        /**
         * @brief Move constructor.
         */
        Job(Job&&) noexcept = default;

        /**
         * @brief Move assignment operator.
         */
        Job& operator=(Job&&) noexcept = default;

        /**
         * @brief Executes this job.
         */
        void execute();

        /**
         * @brief Creates a handle for this job.
         * 
         * @return A handle for this job.
         */
        JobHandle handle() const;
    };
}
