/*
    WorkerThread.cpp

    Implementation of a working thread object.
*/

#include "rendering/scheduling/threading/WorkerThread.hpp"

namespace toxico {
    WorkerThread::WorkerThread(JobQueue& job_queue)
        : queue_(job_queue),
          thread_([this](std::stop_token stop) {
              while (auto job = queue_.pop(stop))
                  job->execute();
          })
    {}

    void WorkerThread::stop() {
        thread_.request_stop();
    }

    WorkerThread::~WorkerThread() {
        thread_.request_stop();
    }
}
