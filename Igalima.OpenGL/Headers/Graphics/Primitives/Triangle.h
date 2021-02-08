//
// Created by Mikyan on 08/02/2021.
//

#ifndef IGALIMA_OPENGL_TRIANGLE_H
#define IGALIMA_OPENGL_TRIANGLE_H

#include <array>
#include <glm/glm.hpp>

class Triangle
{
public:
    Triangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3);
    Triangle(const Triangle&) = default;
    Triangle(Triangle&&) noexcept = default;
    ~Triangle();

public:
    Triangle& operator=(const Triangle&) = default;
    Triangle& operator=(Triangle&&) noexcept = default;

public:
    const float* GetVertices() const;
    const uint32_t& GetSize() const;

private:
    glm::vec2 m_Point1;
    glm::vec2 m_Point2;
    glm::vec2 m_Point3;
    uint32_t m_Size;
    float* m_Vertices;
};

#endif //IGALIMA_OPENGL_TRIANGLE_H
