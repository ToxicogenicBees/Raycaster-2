/*
    JobHandle.hpp

    Declaration of a job handle.
*/

#pragma once

#include "rendering/scheduling/JobState.hpp"
#include <memory>

namespace toxico {
    class JobHandle {
    private:
        std::shared_ptr<JobState> state_;

    public:
        /**
         * @brief Constructor.
         * 
         * @param state This job's state.
         */
        JobHandle(std::shared_ptr<JobState> state);

        /**
         * @brief Gets if the job is finished.
         * 
         * @return If the job is finished.
         */
        bool finished() const;

        /**
         * @brief Gets if the job is cancelled.
         * 
         * @return If the job is cancelled.
         */
        bool cancelled() const;

        /**
         * @brief Cancels the job.
         */
        void cancel();

        /**
         * @brief Yields until the job finishes.
         */
        void wait() const;
    };
}