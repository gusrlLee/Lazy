#pragma once 
#include <iostream>

namespace Lazy 
{
    class Vec2 
    {
        public:
            float e[2];
            Vec2();
            Vec2(float value);
            Vec2(float e1, float e2);

            float x() const { return e[0]; }
            float y() const { return e[1]; }

            Vec2 operator-() const { return Vec2(-e[0], -e[1]); }
            float operator[](int i) const { return e[i]; }
            float &operator[](int i) { return e[i]; }

            Vec2& operator+=(const Vec2 &v)
            {
                e[0] += v.e[0];
                e[1] += v.e[1];
                return *this;
            }

            Vec2& operator*=(const float value)
            {
                e[0] *= value;
                e[1] *= value;
                return *this;
            }

            Vec2& operator/=(const float value)
            {
                return *this *= 1 / value;
            }        
    };
}
