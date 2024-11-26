#pragma once 
#include <iostream>
#include <cmath>

namespace Lazy 
{
    class Vec3 
    {
        public:
            float e[3];

            Vec3();
            Vec3(float value);
            Vec3(float e1, float e2, float e3);

            float x() const { return e[0]; }
            float y() const { return e[1]; }
            float z() const { return e[2]; }

            Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
            float operator[](int i) const { return e[i]; }
            float &operator[](int i) { return e[i]; }

            Vec3& operator+=(const Vec3 &v)
            {
                e[0] += v.e[0];
                e[1] += v.e[1];
                e[2] += v.e[2];
                return *this;
            }

            Vec3& operator*=(const float value)
            {
                e[0] *= value;
                e[1] *= value;
                e[2] *= value;
                return *this;
            }

            Vec3& operator/=(const float value)
            {
                return *this *= 1 / value;
            }        

            float LengthSqaured() const 
            {
                return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
            }

            float Length() const  
            {
                return std::sqrt(this->LengthSqaured());
            }
    };

    inline std::ostream& operator<<(std::ostream& out, const Vec3& v) 
    {
        return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
    }

    inline Vec3 operator+(const Vec3& u, const Vec3& v) 
    {
        return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
    }

    inline Vec3 operator-(const Vec3& u, const Vec3& v) 
    {
        return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
    }

    inline Vec3 operator*(const Vec3& u, const Vec3& v) 
    {
        return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
    }

    inline Vec3 operator*(double t, const Vec3& v) 
    {
        return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
    }

    inline Vec3 operator*(const Vec3& v, double t) 
    {
        return t * v;
    }

    inline Vec3 operator/(const Vec3& v, double t) 
    {
        return (1/t) * v;
    }

    inline double Dot(const Vec3& u, const Vec3& v) 
    {
        return u.e[0] * v.e[0]
            + u.e[1] * v.e[1]
            + u.e[2] * v.e[2];
    }

    inline Vec3 Cross(const Vec3& u, const Vec3& v) 
    {
        return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
    }

    inline Vec3 UnitVector(const Vec3& v) 
    {
        return v / v.Length();
    }


}
