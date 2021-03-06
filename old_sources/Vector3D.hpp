#ifndef INDIE_STUDIO_VECTOR3D_HPP
#define INDIE_STUDIO_VECTOR3D_HPP

#include <ostream>
#include "array"

template <typename T>
class Vector3D {
public:
    Vector3D(T x, T y, T z) : x(x), y(y), z(z)
    {}

    Vector3D(T i) : Vector3D(i, i, i)
    {}

    Vector3D() : Vector3D(0)
    {}

    friend std::ostream &operator <<(std::ostream &os, const Vector3D &d) {
        os << "x: " << d.x << " y: " << d.y << " z: " << d.z;
        return os;
    }

    union {
        struct {
            T x;
            T y;
            T z;
        };
        std::array<T, 3> array;
    };
};

template <typename T>
class Vector2D {
public:
    Vector2D(T x, T y) : x(x), y(y)
    {}

    Vector2D(T i) : Vector2D(i, i)
    {}

    Vector2D() : Vector2D(0)
    {}

    friend std::ostream &operator <<(std::ostream &os, const Vector2D &d) {
        os << "x: " << d.x << " y: " << d.y;
        return os;
    }

    union {
        struct {
            T x;
            T y;
        };
        std::array<T, 2> array;
    };
};

#endif