//
// Created by Mikyan on 15/02/2021.
//

#include <Graphics/Shapes/Rectangle.h>

Rectangle::Rectangle(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height)
{
    X = x;
    Y = y;
    Width = width;
    Height = height;
    
    // Used for translation/scale/rotation with model matrix.
    Position = glm::vec2(X, Y);
    Scale = glm::vec2(1.0f, 1.0f);
    Rotation = glm::vec2(0.0f, 0.0f);
}

Rectangle::Rectangle(const glm::vec2& position, const glm::vec2& dimensions)
{
    X = position.x;
    Y = position.y;
    Width = dimensions.x;
    Height = dimensions.y;
    
    Position = position;
    Scale = glm::vec2(1.0f, 1.0f);
    Rotation = glm::vec2(0.0f, 0.0f);
}