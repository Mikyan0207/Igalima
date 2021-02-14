//
// Created by Mikyan on 14/02/2021.
//

#ifndef IGALIMA_OPENGL_CYCLECOUNTER_H
#define IGALIMA_OPENGL_CYCLECOUNTER_H

#include <cstdint>

class CycleCounter
{
public:
    static void BeginCounter();
    static void EndCounter();

    static int64_t LastCycleCount;
    static int64_t EndCycleCount;
    static int32_t MegaCyclesPerFrame;
};

#endif //IGALIMA_OPENGL_CYCLECOUNTER_H
