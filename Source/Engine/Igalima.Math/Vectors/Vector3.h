#pragma once

#include <cstdint>

namespace Math
{
    template <typename T>
    struct Vector3
    {
        T X;
        T Y;
        T Z;

        Vector3(const T& x, const T& y, const T& z)
        {
            X = x;
            Y = y;
            Z = z;
        }
    };

    using Vector3f = Vector3<float>;
    using Vector3i = Vector3<int32_t>;
    using Vector3u = Vector3<uint32_t>;
};