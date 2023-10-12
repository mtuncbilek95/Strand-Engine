#include "GameTimer.hpp"

GameTimer::GameTimer()
        : m_secondsPerCount(0.0), m_deltaTime(-1.0), m_stopTime(0), m_baseTime(0),
          m_pausedTime(0), m_prevTime(0), m_currTime(0), mStopped(false)
{
    uint64_t countsPerSec{};
    QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
    m_secondsPerCount = 1.0 / (double)countsPerSec;
}

float GameTimer::TotalTime() const
{
    if (mStopped)
    {
        return static_cast<float>(((m_stopTime - m_pausedTime) - m_baseTime) * m_secondsPerCount);
    }

    else
    {
        return static_cast<float>(((m_currTime - m_pausedTime) - m_baseTime) * m_secondsPerCount);
    }
}

float GameTimer::DeltaTime() const
{
    return static_cast<float>(m_deltaTime);
}

void GameTimer::Reset()
{
    uint64_t currTime{};
    QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

    m_baseTime = currTime;
    m_prevTime = currTime;
    m_stopTime = 0;
    mStopped = false;
}

void GameTimer::Start()
{
    unsigned long long startTime{};
    QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

    if (mStopped)
    {
        m_pausedTime += (startTime - m_stopTime);

        m_prevTime = startTime;
        m_stopTime = 0;
        mStopped = false;
    }
}

void GameTimer::Stop()
{
    if (!mStopped)
    {
        uint64_t currTime{};
        QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

        m_stopTime = currTime;
        mStopped = true;
    }
}

void GameTimer::Tick()
{
    if (mStopped)
    {
        m_deltaTime = 0.0;
        return;
    }

    uint64_t currTime{};
    QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
    m_currTime = currTime;

    m_deltaTime = (m_currTime - m_prevTime) * m_secondsPerCount;

    m_prevTime = m_currTime;

    if (m_deltaTime < 0.0)
    {
        m_deltaTime = 0.0;
    }
}