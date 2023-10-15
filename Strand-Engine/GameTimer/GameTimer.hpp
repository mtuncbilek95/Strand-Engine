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
    double m_secondsPerCount;
    double m_deltaTime;

    uint64_t m_baseTime;
    uint64_t m_pausedTime;
    uint64_t m_stopTime;
    uint64_t m_prevTime;
    uint64_t m_currTime;

    bool mStopped;
};