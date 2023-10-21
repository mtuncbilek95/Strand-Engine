// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "JobSystem.hpp"

namespace Strand
{

void JobSystem::Initialize(uint32_t threadCount)
{
    FinishedJobCounter_.store(0);

    auto hardwareCoreCount = std::thread::hardware_concurrency();

    if(threadCount == 0 || threadCount > hardwareCoreCount) {
        threadCount = hardwareCoreCount;
    }

    for(uint32_t threadID = 0; threadID < threadCount; threadID++) {
        std::thread worker([this] {
            std::function<void()> job;

            while(true) {
                if(JobQueue_.Pop(job)) {
                    job();
                    FinishedJobCounter_.fetch_add(1);
                } else {
                    std::unique_lock<std::mutex> lock(JobQueueMutex_);
                    JobQueueCondition_.wait(lock);
                }
            }
        });

        worker.detach();
    }
}

void JobSystem::ExecuteJob(const std::function<void()>& job)
{
    CurrentJob_++;

    while(!JobQueue_.Push(job)) {
        Poll();
    }

    JobQueueCondition_.notify_one();
}

bool JobSystem::IsBusy()
{
    return FinishedJobCounter_.load() < CurrentJob_;
}

void JobSystem::Wait()
{
    while(IsBusy()) {
        Poll();
    }
}

void JobSystem::Dispatch(uint32_t workCount, uint32_t groupCount, const std::function<void(JobDispatchArgs)>& job)
{
// TODO: Implement this
}

} // Strand