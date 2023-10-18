#include "GameTimer.hpp"

GameTimer::GameTimer()
        : SecondsPerCount_(0.0), DeltaTime_(-1.0), StopTime_(0), BaseTime_(0),
          PausedTime_(0), PrevTime_(0), CurrTime_(0), Stopped_(false)
{
    uint64_t countsPerSec{};
    QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
    SecondsPerCount_ = 1.0 / (double)countsPerSec;
}

float GameTimer::TotalTime() const
{
    if (Stopped_)
    {
        return static_cast<float>(((StopTime_ - PausedTime_) - BaseTime_) * SecondsPerCount_);
    }

    else
    {
        return static_cast<float>(((CurrTime_ - PausedTime_) - BaseTime_) * SecondsPerCount_);
    }
}

float GameTimer::DeltaTime() const
{
    return static_cast<float>(DeltaTime_);
}

void GameTimer::Reset()
{
    uint64_t currTime{};
    QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

    BaseTime_ = currTime;
    PrevTime_ = currTime;
    StopTime_ = 0;
    Stopped_ = false;
}

void GameTimer::Start()
{
    unsigned long long startTime{};
    QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

    if (Stopped_)
    {
        PausedTime_ += (startTime - StopTime_);

        PrevTime_ = startTime;
        StopTime_ = 0;
        Stopped_ = false;
    }
}

void GameTimer::Stop()
{
    if (!Stopped_)
    {
        uint64_t currTime{};
        QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

        StopTime_ = currTime;
        Stopped_ = true;
    }
}

void GameTimer::Tick()
{
    if (Stopped_)
    {
        DeltaTime_ = 0.0;
        return;
    }

    uint64_t currTime{};
    QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
    CurrTime_ = currTime;

    DeltaTime_ = (CurrTime_ - PrevTime_) * SecondsPerCount_;

    PrevTime_ = CurrTime_;

    if (DeltaTime_ < 0.0)
    {
        DeltaTime_ = 0.0;
    }
}