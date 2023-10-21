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
        std::thread worker([] {
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

} // Strand