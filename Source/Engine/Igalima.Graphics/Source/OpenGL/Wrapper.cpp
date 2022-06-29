//#include "OpenGL/Wrapper.h"
//
//namespace GL
//{
//#pragma region Buffers
//
//    void Wrapper::GenerateBuffer(u32& id)
//    {
//        glGenBuffers(1, &id);
//    }
//
//    void Wrapper::BindBuffer(const BufferType& type, const u32& id)
//    {
//        glBindBuffer(static_cast<GLenum>(type), id);
//    }
//
//    void Wrapper::DeleteBuffer(u32& id)
//    {
//        glDeleteBuffers(1, &id);
//    }
//
//#pragma endregion Buffers
//
//#pragma region Vertex Array
//
//    void Wrapper::GenerateVertexArray(u32& id)
//    {
//        glGenVertexArrays(1, &id);
//    }
//
//    void Wrapper::BindVertexArray(const u32& id)
//    {
//        glBindVertexArray(id);
//    }
//
//    void Wrapper::DeleteVertexArray(u32& id)
//    {
//        glDeleteVertexArrays(1, &id);
//    }
//    
//#pragma endregion Vertex Array
//
//#pragma region Texture
//
//    void Wrapper::GenerateTexture(u32& id)
//    {
//        glGenTextures(1, &id);
//    }
//
//#pragma endregion Texture
//
//#pragma region Render Buffer
//
//    void Wrapper::GenerateRenderBuffer(u32& id)
//    {
//        glGenRenderbuffers(1, &id);
//    }
//
//    void Wrapper::BindRenderBuffer(const BufferType& type, u32& id)
//    {
//        glBindRenderbuffer(static_cast<GLenum>(type), id);
//    }
//
//    void Wrapper::RenderBufferStorage(const BufferType& type, const InternalFormatType& internalFormat, const u32& width, const u32& height)
//    {
//        glRenderbufferStorage(static_cast<GLenum>(type), static_cast<GLenum>(internalFormat), width, height);
//    }
//
//#pragma endregion Render Buffer
//
//#pragma region Frame Buffer
//
//    void Wrapper::GenerateFrameBuffer(u32& id)
//    {
//        glGenFramebuffers(1, &id);
//    }
//
//#pragma endregion Frame Buffer
//
//    void Wrapper::BufferData(const BufferType& type, const u32& size, const void* vertices, const DrawMode& drawMode)
//    {
//        glBufferData(static_cast<GLenum>(type), size, vertices, static_cast<GLenum>(drawMode));
//    }
//}