#include <Windows.h>
#include <xinput.h>

#include <Common/Igalima.h>

namespace Win32 {
    
    void IGALIMA_API LoadXInput()
    {
        // Loading XInput 1.4
        // Should only be available on Windows 10 and 8.
        HMODULE XInputLib = LoadLibraryA("xinput1_4.dll");
        
        // In case we failed to load XInput 1.4, we can try to load
        // an older version of XInput.
        if (XInputLib == nullptr)
        {
            // Loading XInput 9.1.0, supported on Windows Vista, 7 and 8.
            // Since we're only going to use basic XInput functionality,
            // we can try to load this version before 1.3.
            XInputLib = LoadLibraryA("xinput9_1_0.dll");
        }
        
        // Last chance, XInput 1.3 which is part of the DirectX SDK.
        if (XInputLib == nullptr)
        {
            XInputLib = LoadLibraryA("xinput1_3.dll");
        }
        
        if (XInputLib != nullptr)
        {
            // TODO(Mikyan): Load GetState & SetState functions.
        }
        else
        {
            // TODO(Mikyan): Error message.
        }
    }
};