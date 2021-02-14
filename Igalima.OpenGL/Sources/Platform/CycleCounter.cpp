//
// Created by Mikyan on 14/02/2021.
//

#include <Platform/CycleCounter.h>
#include <Windows.h>

int64_t CycleCounter::LastCycleCount = 0;
int64_t CycleCounter::EndCycleCount = 0;
int32_t CycleCounter::MegaCyclesPerFrame = 0;

// Use the __rdtsc instruction which returns the processor time stamp.
// Returns a 64 bit unsigned integer representing a tick count.
// See https://docs.microsoft.com/en-us/cpp/intrinsics/rdtsc for more information.

void CycleCounter::BeginCounter()
{
    LastCycleCount = __rdtsc();
}

void CycleCounter::EndCounter()
{
    EndCycleCount = __rdtsc();

    MegaCyclesPerFrame = static_cast<int32_t>((EndCycleCount - LastCycleCount) / (1000 * 1000));
    LastCycleCount = EndCycleCount;
}