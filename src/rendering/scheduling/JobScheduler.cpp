/*
    JobScheduler.cpp

    Implementation of a job scheduler.
*/

#include "rendering/scheduling/JobScheduler.hpp"
#include <thread>

namespace toxico {
    JobScheduler::JobScheduler()
        : pool_(std::thread::hardware_concurrency() - 1) {}

    JobHandle JobScheduler::submit(std::function<void()> task) {
        return pool_.submit(task);
    }

    JobBatchHandle JobScheduler::submit(JobBatch batch) {
        std::vector<JobHandle> handles;
        
        while (!batch.empty())
            handles.push_back(submit(batch.pop()));

        return JobBatchHandle(handles.begin(), handles.end());
    }

    std::size_t JobScheduler::threads() const {
        return pool_.threads();
    }
}
