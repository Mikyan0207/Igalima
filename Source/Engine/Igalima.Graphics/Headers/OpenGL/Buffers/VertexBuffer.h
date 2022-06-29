#pragma once

#include "Igalima.Graphics.h"
#include "OpenGL/BufferType.h"
#include "OpenGL/DrawMode.h"
#include "Types.h"
#include <vector>

namespace GL
{
    class IGALIMA_GRAPHICS_API VertexBuffer
    {
    public:
        VertexBuffer(const u32& size, const DrawMode& drawMode);
        VertexBuffer(const float* vertices, const u32& size, const DrawMode& drawMode);
        VertexBuffer(const std::vector<float>& vertices, const DrawMode& drawMode);
        VertexBuffer(const VertexBuffer&) = default;
        VertexBuffer(VertexBuffer&&) noexcept = default;
        ~VertexBuffer();

    public:
        VertexBuffer& operator=(const VertexBuffer&) = default;
        VertexBuffer& operator=(VertexBuffer&&) noexcept = default;

    public:
        void Bind() const;
        void Unbind() const;
        void Delete();

    public:
        const u32& GetId() const;

    private:
        void Initialize(const u32& size, const void* vertices, const DrawMode& drawMode);

    private:
        u32 m_Id;
        DrawMode m_DrawMode;
    };
}