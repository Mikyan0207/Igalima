#include "Window/Window.h"

int main()
{
    auto* window = new Win32::Window();

    window->Initialize(Win32::WindowCreateInfo
        {
            "Igalima", 1280, 720
        });

    while (window->IsOpen())
    {
        window->PollEvents();
        window->Swap_Buffers();
    }

    delete window;
    return 0;
}