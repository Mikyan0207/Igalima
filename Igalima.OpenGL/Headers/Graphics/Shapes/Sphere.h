//
// Created by Mikyan on 10/02/2021.
//

#ifndef IGALIMA_OPENGL_SPHERE_H
#define IGALIMA_OPENGL_SPHERE_H

#define _USE_MATH_DEFINES

#include <vector>
#include <cstdint>
#include <math.h>
#include <OpenGL/GLWrapper.h>
#include <OpenGL/GLVertexArray.h>
#include <OpenGL/GLVertexBuffer.h>
#include <OpenGL/GLIndexBuffer.h>
#include <OpenGL/GLShader.h>
#include <memory>

class Sphere
{
public:
    Sphere(const uint32_t& sectors, const uint32_t& stacks);
    Sphere(const Sphere&) = default;
    Sphere(Sphere&&) noexcept = default;
    ~Sphere();

public:
    Sphere& operator=(const Sphere&) = default;
    Sphere& operator=(Sphere&&) noexcept = default;

public:
    void Draw(GLShader& shader);
    void Delete();

public:
    void SetSize(const uint32_t& sectors, const uint32_t& stacks);

public:
    const uint32_t& GetVerticesCount() const;
    const uint32_t& GetIndicesCount() const;

private:
    void Initialize(const uint32_t& sectors, const uint32_t& stacks);

private:
    GLVertexArray* m_VertexArray;
    uint32_t m_Stacks;
    uint32_t m_Sectors;
    uint32_t m_VerticesCount;
    uint32_t m_IndicesCount;
};

#endif //IGALIMA_OPENGL_SPHERE_H
