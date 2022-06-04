#pragma once

#include "Types.h"

namespace Win32
{
    /// <summary>
    ///     The WindowCreateInfo struct.
    ///     This struct contains information for the creation of a Win32 window.
    /// </summary>
    struct WindowCreateInfo
    {
        const char* Title;
        u32         Width;
        u32         Height;
    };
}