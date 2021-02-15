//
// Created by Mikyan on 15/02/2021.
//

#include <Core/Clock.h>

void Clock::Start()
{
    m_LastClockCall = clock();
}

void Clock::Reset()
{
    m_LastClockCall = clock();
}

float Clock::GetElapsedTime()
{
    return static_cast<float>(clock() - m_LastClockCall);
}

float Clock::GetElapsedTimeAsSeconds()
{
    return static_cast<float>((clock() - m_LastClockCall) / CLOCKS_PER_SEC);
}