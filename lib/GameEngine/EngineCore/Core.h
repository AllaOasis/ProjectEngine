#pragma once
#include <cmath>

namespace GameEngine
{
    struct vector3
    {
    public:
        float x, y, z;

        vector3()
        {
            x = y = z = 0.0f;
        }

        vector3(float _x, float _y, float _z)
        {
            x = _x;
            y = _y;
            z = _z;
        }

        vector3 operator+(const vector3& _other) const
        {
            return {x + _other.x, y + _other.y, z + _other.z};
        }

        vector3& operator+=(const vector3& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        float magnitude() const
        {
            return std::sqrt(x * x + y * y + z * z);
        }
    };

    struct Color
    {
    public:
        float r, g, b, a = 1.0f;
    };

    struct Transform
    {
    public:
        vector3 position = vector3();
        vector3 rotation = vector3();
        vector3 scale = vector3(1, 1, 1);
    };
}
