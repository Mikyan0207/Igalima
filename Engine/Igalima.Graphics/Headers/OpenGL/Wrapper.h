#pragma once

#include "BufferType.h"
#include "DrawMode.h"
#include "InternalFormatType.h"
#include "glad/glad.h"
#include "Igalima.Graphics.h"
#include "Types.h"

namespace GL
{
    class IGALIMA_GRAPHICS_API Wrapper
    {
    public:
        /*static void GenerateBuffer(u32& id);
        static void DeleteBuffer(u32& id);
        static void BindBuffer(const BufferType& type, const u32& id);

        static void GenerateVertexArray(u32& id);
        static void DeleteVertexArray(u32& id);
        static void BindVertexArray(const u32& id);
        
        static void GenerateTexture(u32& id);

        static void GenerateRenderBuffer(u32& id);
        static void BindRenderBuffer(const BufferType& type, u32& id);
        static void RenderBufferStorage(const BufferType& type, const InternalFormatType& internalFormat, const u32& width, const u32& height);

        static void GenerateFrameBuffer(u32& id);

        static void BufferData(const BufferType& type, const u32& size, const void* vertices, const DrawMode& drawMode);*/
    };
}