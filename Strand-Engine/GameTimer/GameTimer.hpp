#pragma once

#include <Common/Common.hpp>

// @brief GameTimer class to calculate delta time and total time.
class STRAND_API GameTimer
{
public:
    GameTimer();

    float TotalTime() const;
    float DeltaTime() const;

    void Reset();
    void Start();
    void Stop();
    void Tick();

private:
    double SecondsPerCount_;
    double DeltaTime_;

    uint64_t BaseTime_;
    uint64_t PausedTime_;
    uint64_t StopTime_;
    uint64_t PrevTime_;
    uint64_t CurrTime_;

    bool Stopped_;
};