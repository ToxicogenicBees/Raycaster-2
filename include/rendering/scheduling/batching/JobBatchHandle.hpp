/*
    JobbatchHandle.hpp

    Declaration of a job batch handle.
*/

#pragma once

#include "rendering/scheduling/JobHandle.hpp"
#include <vector>
#include <concepts>

namespace toxico {
    class JobBatchHandle {
    private:
        std::vector<JobHandle> handles_;

    public:
        /**
         * @brief Constructor.
         * 
         * @param begin The beginning of a container of job handles.
         * @param end The end of a container of job handles.
         */
        template<typename Iter>
        requires std::input_iterator<Iter> && std::same_as<std::iter_value_t<Iter>, JobHandle>
        JobBatchHandle(Iter begin, Iter end);

        /**
         * @brief Gets if the batch is finished.
         * 
         * @return If the batch is finished.
         */
        bool finished() const;

        /**
         * @brief Gets if the batch is cancelled.
         * 
         * @return If the batch is cancelled.
         */
        bool cancelled() const;

        /**
         * @brief Cancels the batch.
         */
        void cancel();

        /**
         * @brief Yields until the batch finishes.
         */
        void wait() const;
    };
}

#include "rendering/scheduling/batching/JobBatchHandle.tpp"
