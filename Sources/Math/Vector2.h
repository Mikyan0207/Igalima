#ifndef _VECTOR2_H
#define _VECTOR2_H

#include <Common/Types.h>

namespace Math
{
    template<typename T>
        struct Vector2
    {
        T X;
        T Y;
    };
    
    using Vector2f = Vector2<f32>;
    using Vector2i = Vector2<i32>;
    using Vector2u = Vector2<u32>;
};
#endif //_VECTOR2_H
