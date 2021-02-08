//
// Created by Mikyan on 08/02/2021.
//

#include <Graphics/Primitives/Triangle.h>

Triangle::Triangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3)
{
    m_Point1 = p1;
    m_Point2 = p2;
    m_Point3 = p3;

    m_Vertices = new float[9];
    m_Vertices[0] = p1.x;
    m_Vertices[1] = p1.y;
    m_Vertices[2] = 0.0f;
    m_Vertices[3] = p2.x;
    m_Vertices[4] = p2.y;
    m_Vertices[5] = 0.0f;
    m_Vertices[6] = p3.x;
    m_Vertices[7] = p3.y;
    m_Vertices[8] = 0.0f;

    m_Size = 9 * sizeof(float);
}

Triangle::~Triangle()
{
    delete[] m_Vertices;
}

const float* Triangle::GetVertices() const
{
    return m_Vertices;
}

const uint32_t& Triangle::GetSize() const
{
    return m_Size;
}