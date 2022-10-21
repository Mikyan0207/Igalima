#pragma once

#include <cstdint>

namespace Math
{
    template<typename T>
    struct Vector2
    {
        T X;
        T Y;

        Vector2(const T& x, const T& y)
        {
            X = x;
            Y = y;
        }
    };

    using Vector2f = Vector2<float>;
    using Vector2i = Vector2<int32_t>;
    using Vector2u = Vector2<uint32_t>;
}