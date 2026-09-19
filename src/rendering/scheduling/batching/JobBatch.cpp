/*
    JobBatch.cpp

    Implementation of a job batch, a set of jobs related to each other.
*/

#include "rendering/scheduling/batching/JobBatch.hpp"
#include <vector>

namespace toxico {
    void JobBatch::push(std::function<void()> task) noexcept {
        tasks_.push(std::move(task));
    }

    std::function<void()> JobBatch::pop() {
        auto task = std::move(tasks_.front());
        tasks_.pop();

        return task;
    }

    bool JobBatch::empty() const noexcept {
        return tasks_.empty();
    }

    std::size_t JobBatch::size() const noexcept {
        return tasks_.size();
    }
}
