#pragma once

#include "Vectors/Vector3.h"

namespace Graphics
{
    using namespace Math;

#pragma pack(push, 1)
    struct Vertex
    {
        Vector3f Position;
        Vector3f Normal;
        Vector3f TextureCoordinate;
        Vector3f Tangent;
        Vector3f Bitangent;
    };
#pragma pack(pop)
}