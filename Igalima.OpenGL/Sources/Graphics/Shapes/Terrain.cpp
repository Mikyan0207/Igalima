#include <Graphics/Shapes/Terrain.h>

Terrain::Terrain(const uint32_t& size)
{
    const float SIZE = 10000; // Make this value configurable.
    m_Size = size;
    auto vertices = std::vector<float>(m_Size * m_Size * 3);
    auto indices = std::vector<uint32_t>(6 * (m_Size - 1) * (m_Size - 1));

    // @Note:
    // Refactor this to remove warnings.
    int vertexPointer = 0;
    for (float i = 0; i < m_Size; i++) { // z
        for (float j = 0; j < m_Size; j++) { // x
            vertices[vertexPointer * 3] = (float)j / ((float)m_Size - 1) * SIZE;
            vertices[vertexPointer * 3 + 1] = 0;
            vertices[vertexPointer * 3 + 2] = (float)i / ((float)m_Size - 1) * SIZE;
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

    std::cout << "Terrain Vertices: " << m_VerticesCount << std::endl;
    std::cout << "Terrain Indices: " << m_IndicesCount << std::endl;

    auto vbo = std::make_unique<GLVertexBuffer>(vertices, GLDrawMode::STATIC);

    GLWrapper::VertexAttributePointer(0, 3, GL_FLOAT, 3 * sizeof(float), 0);

    auto ebo = std::make_unique<GLIndexBuffer>(indices, GLDrawMode::STATIC);

    m_VertexArray.AddBuffer(vbo);
    m_VertexArray.AddBuffer(ebo);

    // Init Shader
    m_Shader = GLShader("Resources/Shaders/Terrain/Terrain_Vertex.glsl", "Resources/Shaders/Terrain/Terrain_Fragment.glsl");

    m_Shader.Use();
    m_Shader.SetInt("NoiseTexture", 0);
    m_Shader.SetFloat("GridSize", m_Size);
    m_Shader.Unbind();

    // Load Texture.
    m_NoiseTexture = new Texture("Resources/heightmap.png");
}

Terrain::~Terrain()
{
    delete m_NoiseTexture;
}

void Terrain::Draw()
{
    glActiveTexture(GL_TEXTURE0);
    m_NoiseTexture->Bind();
    m_Shader.Use();

    m_VertexArray.Bind();
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