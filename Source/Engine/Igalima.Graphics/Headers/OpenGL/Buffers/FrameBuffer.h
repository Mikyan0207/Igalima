#pragma once

#include "Igalima.Graphics.h"
#include "Types.h"

namespace GL
{
    class IGALIMA_GRAPHICS_API FrameBuffer
    {
    public:
        FrameBuffer(const u32& width, const u32& height, const u32& originalWidth, const u32& originalHeight);
        FrameBuffer(const FrameBuffer&) = default;
        FrameBuffer(FrameBuffer&&) noexcept = default;
        ~FrameBuffer();

    public:
        FrameBuffer& operator=(const FrameBuffer&) = default;
        FrameBuffer& operator=(FrameBuffer&&) noexcept = default;

    public:
        void Bind() const;
        void Unbind() const;
        void Delete() const;

    public:
        const u32& GetId() const;
        const u32& GetColorAttachmentId() const;
        const u32& GetRenderBufferId() const;

    private:
        u32 m_Id;
        u32 m_ColorAttachmentId;
        u32 m_RenderBufferId;
        u32 m_Width;
        u32 m_Height;
        u32 m_OriginalWidth;
        u32 m_OriginalHeight;
    };
}