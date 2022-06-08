#pragma once

#include "OpenGL/DrawMode.h"
#include "OpenGL/BufferType.h"
#include "glad/glad.h"
#include "Igalima.Graphics.h"
#include "Types.h"
#include <vector>

namespace GL
{
    class IGALIMA_GRAPHICS_API IndexBuffer
    {
    public:
        IndexBuffer(const u32* indices, const u32& size, const DrawMode& drawMode);
        IndexBuffer(const std::vector<u32>& indices, const DrawMode& drawMode);
        IndexBuffer(const IndexBuffer&) = default;
        IndexBuffer(IndexBuffer&&) noexcept = default;
        ~IndexBuffer();

    public:
        IndexBuffer& operator=(const IndexBuffer&) = default;
        IndexBuffer& operator=(IndexBuffer&&) noexcept = default;

    public:
        void Bind() const;
        void Unbind() const;
        void Delete();

    public:
        const u32& GetId() const;

    private:
        void Initialize(const BufferType& type, const u32& size, const u32* indices, const DrawMode& drawMode);

    private:
        u32 m_Id;

        DrawMode m_DrawMode;

        BufferType m_Type = BufferType::ElementArrayBuffer;
    };
}