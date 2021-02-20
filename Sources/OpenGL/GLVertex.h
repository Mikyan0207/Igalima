#ifndef _GL_VERTEX_H
#define _GL_VERTEX_H

#include <Math/Vector2.h>
#include <Math/Vector3.h>

struct GLVertex
{
    Math::Vector3f Position;
    Math::Vector2f TextureCoordinates;
    Math::Vector3f Normal;
};

#endif //_GL_VERTEX_H
