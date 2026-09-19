/*
    JobScheduler.hpp

    Declaration of a job scheduler.
*/

#pragma once

#include "foundation/containers/OwningVector.hpp"
#include "rendering/scheduling/threading/ThreadPool.hpp"
#include "rendering/scheduling/batching/JobBatchHandle.hpp"
#include "rendering/scheduling/batching/JobBatch.hpp"
#include "rendering/scheduling/JobHandle.hpp"
#include <functional>
#include <memory>

namespace toxico {
    class JobScheduler {
    private:
        ThreadPool pool_;

    public:
        /**
         * @brief Constructor.
         */
        JobScheduler();

        /**
         * @brief Submit a job to the background pool.
         * 
         * @param pool The pool being submitted to.
         * @param task The task being submitted.
         * @return A handle for the submitted job.
         */
        JobHandle submit(std::function<void()> task);

        /**
         * @brief Submit a job batch to the background pool.
         * 
         * @param pool The pool being submitted to.
         * @param batch The job batch being submitted.
         * @return A handle for the submitted job.
         */
        JobBatchHandle submit(JobBatch batch);

        /**
         * @brief Gets the number of threads in the specified pool.
         * 
         * @param pool The pool being checked.
         * @return The number of threads in the specified pool.
         */
        std::size_t threads() const;
    };
}
