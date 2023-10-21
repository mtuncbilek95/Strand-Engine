// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <Common/Singleton.hpp>

#include <JobSystem/JobDispatchArgs.hpp>
#include <JobSystem/ThreadSafeStack.hpp>

namespace Strand
{
// @brief This is a job system that is used to run tasks in parallel.
class JobSystem : public Singleton<JobSystem>
{
public:
    JobSystem() = default;
    ~JobSystem() = default;

    // @brief Initializes the job system.
    // @param threadCount The number of threads to use when running jobs.
    void Initialize(uint32_t threadCount);

    void ExecuteJob(const std::function<void()>& job);
    void Dispatch(uint32_t workCount, uint32_t groupCount, const std::function<void(JobDispatchArgs)>& job);

    bool IsBusy();
    void Wait();

private:
    FORCEINLINE void Poll()
    {
        JobQueueCondition_.notify_one();
        std::this_thread::yield();
    }

private:
    uint32_t ThreadCount_ = 0;
    ThreadSafeStack<std::function<void()>, 256> JobQueue_;
    std::condition_variable JobQueueCondition_;
    std::mutex JobQueueMutex_;
    uint64_t CurrentJob_ = 0;
    std::atomic<uint64_t> FinishedJobCounter_ = 0;
};

} // Strand
