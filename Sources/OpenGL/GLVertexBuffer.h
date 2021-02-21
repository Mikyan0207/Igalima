#ifndef _GL_VERTEX_BUFFER_H
#define _GL_VERTEX_BUFFER_H

#include <OS/glad.h>

#include <Common/Types.h>
#include <Common/Igalima.h>

class IGALIMA_API GLVertexBuffer
{
    public:
    GLVertexBuffer(f32* vertices, u32 size, u32 drawMode);
    ~GLVertexBuffer();
    
    public:
    void Bind();
    void Unbind();
    
    public:
    u32 Id;
};

#endif //_GL_VERTEX_BUFFER_H