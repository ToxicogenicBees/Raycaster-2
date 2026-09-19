/*
    Job.cpp

    Implementation of a job object.
*/

#include "rendering/scheduling/Job.hpp"

namespace toxico {
    Job::Job(std::function<void()> task, std::function<void()> on_complete)
        : state_(std::make_shared<JobState>()),
          on_complete_(on_complete),
          task_(task)
    {
        state_->processing.add();
    }

    void Job::execute() {
        if (!state_->canceled)
            task_();

        state_->processing.complete();
            
        if (on_complete_)
            on_complete_();
    }

    JobHandle Job::handle() const {
        return JobHandle(state_);
    }
}
