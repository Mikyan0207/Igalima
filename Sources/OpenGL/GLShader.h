#ifndef _GL_SHADER_H
#define _GL_SHADER_H

#include <iostream>
#include <fstream>

#include <OS/glad.h>

#include <Common/Types.h>
#include <Common/Igalima.h>
#include <Memory/StackAllocator.h>

class IGALIMA_API GLShader
{
    public:
    GLShader(Memory::StackAllocator* allocator);
    ~GLShader() = default;
    
    public:
    void CreateShader(char* vertex, char* fragment);
    
    public:
    void Bind();
    void Unbind();
    void Delete();
    
    private:
    bool LoadShader(char* file, u32 type);
    static void CheckErrors(u32 id);
    
    public:
    u32 ProgramId = 0;
    u32 VertexId = 0;
    u32 FragmentId = 0;
    
    private:
    Memory::StackAllocator* m_Allocator;
};

#endif //_GL_SHADER_H
