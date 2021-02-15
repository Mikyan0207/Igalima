//
// Created by Mikyan on 15/02/2021.
//

#ifndef _CLOCK_H
#define _CLOCK_H

#include <ctime>

// NOTE(mikyan): Maybe use std::chrono or anything else.
// clock doesn't look accurate at all.
class Clock
{
    public:
    Clock() = default;
    Clock(const Clock&) = delete;
    Clock(Clock&&) noexcept = delete;
    ~Clock() = default;
    
    public:
    Clock& operator=(const Clock&) = delete;
    Clock& operator=(Clock&&) noexcept = delete;
    
    public:
    void Start();
    void Reset();
    
    public:
    float GetElapsedTime();
    float GetElapsedTimeAsSeconds();
    
    private:
    clock_t m_LastClockCall;
};

#endif //_CLOCK_H
