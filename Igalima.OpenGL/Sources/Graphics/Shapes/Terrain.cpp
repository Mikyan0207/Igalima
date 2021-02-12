#include <Graphics/Shapes/Terrain.h>

Terrain::Terrain(const uint32_t& size)
{
    const float SIZE = 1080; // Make this value configurable.
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

            textureCoords[vertexPointer * 2] = (float)j / ((float)m_Size - 1);
            textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)m_Size - 1);
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

    std::cout << "Terrain Vertices: " << m_VerticesCount << std::endl;
    std::cout << "Terrain Indices: " << m_IndicesCount << std::endl;
    std::cout << "Terrain TexCoords: " << m_TextureCoordinatesCount << std::endl;

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
    m_Shader.SetInt("NoiseTexture", 0);
    m_Shader.Unbind();

    heightmap = new Texture("Resources/heightmap.png");
}

Terrain::~Terrain()
{
}

void Terrain::Draw(const uint32_t& textureId)
{
    m_Shader.Use();

    m_VertexArray.Bind();
    glActiveTexture(GL_TEXTURE0);
    heightmap->Bind();
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