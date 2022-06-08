#pragma once

#include "BufferType.h"
#include "DrawMode.h"
#include "glad/glad.h"
#include "Igalima.Graphics.h"
#include "Types.h"

namespace GL
{
    class IGALIMA_GRAPHICS_API Wrapper
    {
    public:
        static void GenerateBuffer(u32& id);
        static void DeleteBuffer(u32& id);
        static void BindBuffer(const BufferType& type, const u32& id);
        static void BufferData(const BufferType& type, const u32& size, const void* vertices, const DrawMode& drawMode);
    };
}