/*
    JobbatchHandle.cpp

    Implementation of a job batch handle.
*/

#include "rendering/scheduling/batching/JobBatchHandle.hpp"

namespace toxico {
    bool JobBatchHandle::finished() const {
        for (auto handle : handles_) {
            if (!handle.finished())
                return false;
        }

        return true;
    }

    bool JobBatchHandle::cancelled() const {
        for (auto handle : handles_) {
            if (!handle.finished())
                return false;
        }

        return true;
    }

    void JobBatchHandle::cancel() {
        for (auto handle : handles_)
            handle.cancel();
    }

    void JobBatchHandle::wait() const {
        for (auto handle : handles_)
            handle.wait();
    }
}
