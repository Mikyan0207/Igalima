#include <Graphics/Shapes/Terrain.h>

Terrain::Terrain(const uint32_t& size, const uint32_t& heightmapId)
{
    const float SIZE = 10000; // Make this value configurable.
    m_Size = size;
    auto vertices = std::vector<float>(m_Size * m_Size * 3);
    auto indices = std::vector<uint32_t>(6 * (m_Size - 1) * (m_Size - 1));
    auto textureCoords = std::vector<float>(m_Size * m_Size * 2);

    // @Note:
    // Refactor this to remove warnings.
    int vertexPointer = 0;
    for (float i = 0; i < m_Size; i++) { // z
        for (float j = 0; j < m_Size; j++) { // x
            vertices[vertexPointer * 3] = (float)j / ((float)m_Size - 1) * SIZE;
            vertices[vertexPointer * 3 + 1] = 0;
            vertices[vertexPointer * 3 + 2] = (float)i / ((float)m_Size - 1) * SIZE;

            textureCoords[vertexPointer * 2] = (float)(j / ((float)m_Size - 1));
            textureCoords[vertexPointer * 2 + 1] = (float)(i / ((float)m_Size - 1));
            vertexPointer++;
        }
    }

    int pointer = 0;
    for (int gz = 0; gz < m_Size - 1; gz++) {
        for (int gx = 0; gx < m_Size - 1; gx++) {
            int topLeft = (gz * m_Size) + gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz + 1) * m_Size) + gx;
            int bottomRight = bottomLeft + 1;
            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }
    }

    m_VerticesCount = vertices.size();
    m_IndicesCount = indices.size();
    m_TextureCoordinatesCount = textureCoords.size();

    auto vbo = std::make_unique<GLVertexBuffer>(vertices, GLDrawMode::STATIC);
    GLWrapper::VertexAttributePointer(0, 3, GL_FLOAT, 3 * sizeof(float), 0);

    auto vbo2 = std::make_unique<GLVertexBuffer>(textureCoords, GLDrawMode::STATIC);
    GLWrapper::VertexAttributePointer(1, 2, GL_FLOAT, 2 * sizeof(float), 0);

    auto ebo = std::make_unique<GLIndexBuffer>(indices, GLDrawMode::STATIC);

    m_VertexArray.AddBuffer(vbo);
    m_VertexArray.AddBuffer(vbo2);
    m_VertexArray.AddBuffer(ebo);

    // Init Shader
    m_Shader = GLShader("Resources/Shaders/Terrain/Terrain_Vertex.glsl", "Resources/Shaders/Terrain/Terrain_Fragment.glsl");

    m_Shader.Use();
    m_HeightmapId = heightmapId;
    glBindTexture(GL_TEXTURE_2D, m_HeightmapId);
    m_Shader.SetInt("NoiseTexture", 0);
    m_GrassTexture = new Texture("Resources/Textures/Grass/Grass_2K_Albedo.jpg");
    m_Shader.SetInt("GrassTexture", 1);
    m_Shader.Unbind();
}

Terrain::~Terrain()
{
}

void Terrain::Draw()
{
    m_Shader.Use();
    m_VertexArray.Bind();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_HeightmapId);

    glActiveTexture(GL_TEXTURE1);
    m_GrassTexture->Bind();

    GLWrapper::DrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, 0);
    m_VertexArray.Unbind();

    m_Shader.Unbind();
}

void Terrain::SetMVP(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
    m_Shader.Use();
    m_Shader
        .SetMat4("model", model)
        .SetMat4("view", view)
        .SetMat4("projection", projection);
    m_Shader.Unbind();
}