#ifndef _GL_INDEX_BUFFER_H
#define _GL_INDEX_BUFFER_H

#include <OS/glad.h>
#include <Common/Types.h>
#include <Common/Igalima.h>

class IGALIMA_API GLIndexBuffer
{
    public:
    GLIndexBuffer(u32* indices, u32 size, u32 drawMode);
    ~GLIndexBuffer();
    
    public:
    void Bind();
    void Unbind();
    
    private:
    u32 Id;
};

#endif //_GL_INDEX_BUFFER_H
