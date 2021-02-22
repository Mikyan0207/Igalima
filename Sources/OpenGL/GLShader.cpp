#include <OpenGL/GLShader.h>

GLShader::GLShader(Memory::StackAllocator* allocator)
{
    m_Allocator = allocator;
}

void GLShader::CreateShader(char* vertex, char* fragment)
{
    ProgramId = glCreateProgram();
    
    // TODO(Mikyan): Check link status.
    glLinkProgram(ProgramId);
    
    LoadShader(vertex, GL_VERTEX_SHADER);
    LoadShader(fragment, GL_FRAGMENT_SHADER);
    
    if (VertexId != 0)
        glDeleteShader(VertexId);
    
    if (FragmentId != 0)
        glDeleteShader(FragmentId);
}

void GLShader::Bind()
{
    glUseProgram(ProgramId);
}

void GLShader::Unbind()
{
    glUseProgram(0);
}

void GLShader::Delete()
{
    if (ProgramId != 0)
        glDeleteProgram(ProgramId);
}

bool GLShader::LoadShader(char *file, u32 type)
{
    std::ifstream is(file);
    
    if (!is.is_open())
        return false;
    
    is.seekg(0, is.end);
    size_t size = is.tellg();
    is.seekg(0, is.beg);
    
    
    char* content = (char*)m_Allocator->Alloc(static_cast<u32>(size));
    
    // Check if we succesfully allocated our buffer
    // since it could fail if our allocator is too small.
    if (!content)
        return false;
    
    is.read(content, size);
    is.close();
    
    if (type == GL_VERTEX_SHADER)
    {
        VertexId = glCreateShader(GL_VERTEX_SHADER);
        
        glShaderSource(VertexId, 1, &content, nullptr);
        glCompileShader(VertexId);
        CheckErrors(VertexId);
        glAttachShader(ProgramId, VertexId);
    }
    else if (type == GL_FRAGMENT_SHADER)
    {
        FragmentId = glCreateShader(GL_FRAGMENT_SHADER);
        
        glShaderSource(FragmentId, 1, &content, nullptr);
        glCompileShader(FragmentId);
        CheckErrors(FragmentId);
        glAttachShader(ProgramId, FragmentId);
    }
    
    return true;
}

void GLShader::CheckErrors(u32 id)
{
    // Clean-up this. I don't remember exactly what to use.
    // But we can call glGetShaderInfoLog using the exact
    // log message length.
    // Check OpenGL official doc!
    int success;
	char infoLog[512];
    
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(id, 512, nullptr, infoLog);
		std::cerr << "[GLShader] Error: " << infoLog << std::endl;
	}
}