/*
    JobHandle.cpp

    Implementation of a job handle.
*/

#include "rendering/scheduling/JobHandle.hpp"
#include <thread>

namespace toxico {
    JobHandle::JobHandle(std::shared_ptr<JobState> state)
        : state_(state) {}

    bool JobHandle::finished() const {
        return state_->processing.pending() == 0;
    }

    bool JobHandle::cancelled() const {
        return state_->canceled;
    }

    void JobHandle::cancel() {
        state_->canceled = true;
    }

    void JobHandle::wait() const {
        state_->processing.wait();
    }
}
