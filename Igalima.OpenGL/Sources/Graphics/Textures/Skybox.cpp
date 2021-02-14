//
// Created by Mikyan on 09/02/2021.
//

#include <Graphics/Textures/Skybox.h>

Skybox::Skybox(const SkyboxSettings& settings)
{
    glGenTextures(1, &m_Id);
    Bind();

    int width, height, channels = 0;
    const auto paths = settings.Textures;

    for (uint32_t i = 0; i < paths.size(); i += 1)
    {
        auto* data = stbi_load(paths[i].c_str(), &width, &height, &channels, 0);

        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cerr << "File " << paths[i] << " not found." << std::endl;
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    m_VertexArray = new GLVertexArray();
    auto vbo = std::make_unique<GLVertexBuffer>(std::vector<float> {
        -1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f
    }, GLDrawMode::STATIC);

    m_VertexArray->AddBuffer(vbo);

    // @Improvement:
    // For now, we assume that location = 0 is the position and it's a vec3
    // Maybe i'll make it configurable later if necessary.
    GLWrapper::VertexAttributePointer(0, 3, GL_FLOAT, 3 * sizeof(float), 0);

#if _DEBUG
    assert(vbo == nullptr); // @Debug: Remove later.
#endif

    m_Shader = new GLShader(settings.VertexShaderPath, settings.FragmentShaderPath);
}

Skybox::Skybox(const std::string& path)
{
    // TODO: Load texture from one file.
    // Calculate & create each skybox face.

    glGenTextures(1, &m_Id);
    Bind();
}

Skybox::~Skybox()
{
    Delete();
}

void Skybox::Bind() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_Id);
}

void Skybox::Unbind() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Skybox::Draw(const glm::mat4& view, const glm::mat4& projection)
{
    GLWrapper::DepthFunction(GL_LEQUAL);
    m_Shader->Use();
    m_Shader->SetMat4("view", view).SetMat4("projection", projection);
    m_VertexArray->Bind();
    ActiveTexture(GL_TEXTURE0);
    Bind();
    GLWrapper::DrawArray(GL_TRIANGLES, 0, 36);
    Unbind();
    m_VertexArray->Unbind();
    m_Shader->Unbind();
    GLWrapper::DepthFunction(GL_LESS);
}

void Skybox::ActiveTexture(const uint32_t& slot)
{
    glActiveTexture(static_cast<GLenum>(slot));
}

void Skybox::Delete() const
{
    if (m_Id != 0)
        glDeleteTextures(1, &m_Id);

    if (m_VertexArray)
        delete m_VertexArray;

    if (m_Shader)
        delete m_Shader;
}