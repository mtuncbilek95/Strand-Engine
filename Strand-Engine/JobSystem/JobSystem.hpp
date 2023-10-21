// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <Common/Singleton.hpp>

#include <JobSystem/JobDispatchArgs.hpp>
#include <JobSystem/ThreadSafeStack.hpp>

namespace Strand
{
// @brief This is a job system that is used to run tasks in parallel.
class ThreadSystem
{
public:
    ThreadSystem() = default;
    ~ThreadSystem() = default;

    static void Initialize();
    static void Shutdown();

    static void AddJob(const std::function<void()>& job);
    static void Dispatch(uint32_t workCount, uint32_t groupCount, const std::function<void(JobDispatchArgs)>& job);

    bool IsBusy();

    void Wait();
private:
    uint32_t ThreadCount = 0;
    ThreadSafeStack<std::function<void()>, 256> JobQueue;
    std::condition_variable JobQueueCondition;
    std::mutex JobQueueMutex;
    uint64_t CurrentJob_ = 0;
    std::atomic<uint64_t> JobCounter_ = 0;
};

} // Strand
