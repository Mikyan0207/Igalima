//
// Created by Mikyan on 10/02/2021.
//

#include <Graphics/Shapes/Sphere.h>

Sphere::Sphere(const uint32_t& sectors, const uint32_t& stacks)
{
    m_Sectors = sectors;
    m_Stacks = stacks;

    Initialize(m_Sectors, m_Stacks);
}

Sphere::~Sphere()
{
    Delete();
}

void Sphere::Draw(GLShader& shader)
{
    shader.Use();

    m_VertexArray->Bind();
    GLWrapper::DrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, nullptr);
    m_VertexArray->Unbind();
}

void Sphere::Delete()
{
    if (m_VertexArray)
        delete m_VertexArray;
}

void Sphere::SetSize(const uint32_t& sectors, const uint32_t& stacks)
{
    m_Sectors = sectors;
    m_Stacks = stacks;

    Initialize(m_Sectors, m_Stacks);
}

const uint32_t& Sphere::GetVerticesCount() const
{
    return m_VerticesCount;
}

const uint32_t& Sphere::GetIndicesCount() const
{
    return m_IndicesCount;
}

void Sphere::Initialize(const uint32_t& sectors, const uint32_t& stacks)
{
    Delete(); // Delete VertexArray if any.

    auto vertices = std::vector<float>();
    auto indices = std::vector<uint32_t>();

    for (uint32_t y = 0; y <= stacks; ++y)
    {
        for (uint32_t x = 0; x <= sectors; ++x)
        {
            float xS = (float)x / (float)sectors;
            float yS = (float)y / (float)stacks;

            float x1 = cos(xS * 2 * M_PI) * sin(yS * M_PI);
            float y1 = cos(yS * M_PI);
            float z1 = sin(xS * 2 * M_PI) * sin(yS * M_PI);

            vertices.push_back(x1);
            vertices.push_back(y1);
            vertices.push_back(z1);
        }
    }

    for (uint32_t y = 0; y < stacks; ++y)
    {
        for (uint32_t x = 0; x < sectors; ++x)
        {
            indices.push_back((y + 1) * (sectors + 1) + x);
            indices.push_back(y * (sectors + 1) + x);
            indices.push_back(y * (sectors + 1) + x + 1);

            indices.push_back((y + 1) * (sectors + 1) + x);
            indices.push_back(y * (sectors + 1) + x + 1);
            indices.push_back((y + 1) * (sectors + 1) + x + 1);
        }
    }

    m_VertexArray = new GLVertexArray();
    m_VerticesCount = vertices.size();
    m_IndicesCount = indices.size();

    auto vbo = std::make_unique<GLVertexBuffer>(vertices, GLDrawMode::STATIC);
    auto ebo = std::make_unique<GLIndexBuffer>(indices, GLDrawMode::STATIC);

    m_VertexArray->AddBuffer(vbo);
    m_VertexArray->AddBuffer(ebo);

    GLWrapper::VertexAttributePointer(0, 3, GL_FLOAT, 3 * sizeof(float), 0);
}
