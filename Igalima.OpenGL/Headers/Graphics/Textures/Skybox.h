//
// Created by Mikyan on 09/02/2021.
//

#ifndef IGALIMA_OPENGL_SKYBOX_H
#define IGALIMA_OPENGL_SKYBOX_H

#include <cstdint>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <stb/stb_image.h>
#include <glad/glad.h>
#include <OpenGL/GLShader.h>
#include <OpenGL/GLVertexArray.h>
#include <OpenGL/GLVertexBuffer.h>
#include <OpenGL/GLWrapper.h>

class Skybox
{
public:
    Skybox(const std::vector<std::string>& paths);
    Skybox(const std::string& path);
    Skybox(const Skybox&) = default;
    Skybox(Skybox&&) noexcept = default;
    ~Skybox();

public:
    Skybox& operator=(const Skybox&) = default;
    Skybox& operator=(Skybox&&) noexcept = default;

public:
    void Bind() const;
    void Unbind() const;
    void Draw(GLShader& shader);
    void ActiveTexture(const uint32_t& slot);
    void Delete() const;

private:
    uint32_t m_Id;
    GLVertexArray* m_VertexArray;
};

#endif //IGALIMA_OPENGL_SKYBOX_H
