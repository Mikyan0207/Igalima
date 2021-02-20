#ifndef _VECTOR3_H
#define _VECTOR3_H

#include <Common/Types.h>

namespace Math
{
    template<typename T>
        struct Vector3
    {
        T X;
        T Y;
        T Z;
    };
    
    using Vector3f = Vector3<f32>;
    using Vector3i = Vector3<i32>;
    using Vector3u = Vector3<u32>;
};
#endif //_VECTOR3_H
