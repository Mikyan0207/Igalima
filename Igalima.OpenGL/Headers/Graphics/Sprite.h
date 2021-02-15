//
// Created by Mikyan on 15/02/2021.
//

#ifndef _SPRITE_H
#define _SPRITE_H

#include <string>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <Graphics/Shapes/Rectangle.h>
#include <Graphics/Textures/Texture.h>
#include <OpenGL/GLVertexArray.h>
#include <OpenGL/GLVertexBuffer.h>
#include <OpenGL/GLIndexBuffer.h>
#include <OpenGL/GLShader.h>
#include <OpenGL/GLWrapper.h>

class Sprite
{
    public:
    Sprite(const std::string& path);
    Sprite(const Sprite&) = default;
    Sprite(Sprite&&) noexcept = default;
    ~Sprite();
    
    public:
    Sprite& operator=(const Sprite&) = default;
    Sprite& operator=(Sprite&&) noexcept = default;
    
    public:
    void Draw(const glm::mat4& view);
    
    private:
    Rectangle m_Rectangle;
    Texture m_Texture;
    GLShader m_Shader;
    GLVertexArray* m_VertexArray;
};

#endif //_SPRITE_H
