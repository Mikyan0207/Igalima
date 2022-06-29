#pragma once

#include "Igalima.Graphics.h"
#include "OpenGL/Buffers/VertexBuffer.h"
#include "OpenGL/Buffers/IndexBuffer.h"
#include "Types.h"
#include <memory>

namespace GL
{
    class IGALIMA_GRAPHICS_API VertexArray
    {
    public:
        VertexArray();
        VertexArray(const VertexArray&) = default;
        VertexArray(VertexArray&&) noexcept = default;
        ~VertexArray();

    public:
        VertexArray& operator=(const VertexArray&) = default;
        VertexArray& operator=(VertexArray&&) noexcept = default;

    public:
        void Bind() const;
        void Unbind() const;
        void Delete();
        void AddBuffer(std::unique_ptr<VertexBuffer>& buffer);
        void AddBuffer(std::unique_ptr<IndexBuffer>& buffer);
        void RemoveVertexBuffer(const u32& bufferId);
        void RemoveIndexBuffer(const u32& bufferId);

    public:
        VertexBuffer* GetVertexBuffer(const u32& bufferId);
        IndexBuffer* GetIndexBuffer(const u32& bufferId);

    private:
        void Initialize();

    private:
        uint32_t m_Id;
        std::vector<std::unique_ptr<VertexBuffer>> m_VertexBuffers;
        std::vector<std::unique_ptr<IndexBuffer>> m_IndexBuffers;
    };
}