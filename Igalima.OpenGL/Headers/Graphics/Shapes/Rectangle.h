//
// Created by Mikyan on 15/02/2021.
//

#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include <cstdint>

#include <glm/glm.hpp>

class Rectangle
{
    public:
    Rectangle() = default;
    Rectangle(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height);
    Rectangle(const glm::vec2& position, const glm::vec2& dimensions);
    Rectangle(const Rectangle&) = default;
    Rectangle(Rectangle&&) noexcept = default;
    ~Rectangle() = default;
    
    public:
    Rectangle& operator=(const Rectangle&) = default;
    Rectangle& operator=(Rectangle&&) noexcept = default;
    
    public:
    uint32_t X;
    uint32_t Y;
    uint32_t Width;
    uint32_t Height;
    
    public:
    glm::vec2 Position;
    glm::vec2 Scale;
    glm::vec2 Rotation;
};

#endif //_RECTANGLE_H
