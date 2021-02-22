#ifndef _GL_VERTEX_ARRAY_H
#define _GL_VERTEX_ARRAY_H

#include <OS/glad.h>

#include <Common/Types.h>
#include <Common/Igalima.h>

class IGALIMA_API GLVertexArray
{
    public:
    GLVertexArray();
    ~GLVertexArray();
    
    public:
    void Bind();
    void Unbind();
    
    public:
    u32 Id;
};

#endif //_G_L_VERTEX_ARRAY_H
