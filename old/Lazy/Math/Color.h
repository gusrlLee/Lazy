#pragma once 
#include <iostream>
#include "Math/Vec3.h"

namespace Lazy 
{
    class Color 
    {
        public:
            unsigned char e[3];

            Color();
            Color(Vec3 v);
            Color(unsigned char value);
            Color(unsigned char e1, unsigned char e2, unsigned char e3);

            unsigned char r() const { return e[0]; }
            unsigned char g() const { return e[1]; }
            unsigned char b() const { return e[2]; }

            Color operator-() const { return Color(-e[0], -e[1], -e[2]); }
            unsigned char operator[](int i) const { return e[i]; }
            unsigned char &operator[](int i) { return e[i]; }

            Color& operator+=(const Color &c)
            {
                e[0] += c.e[0];
                e[1] += c.e[1];
                e[2] += c.e[2];
                return *this;
            }

            Color& operator*=(const unsigned char value)
            {
                e[0] *= value;
                e[1] *= value;
                e[2] *= value;
                return *this;
            }

            Color& operator/=(const unsigned char value)
            {
                return *this *= 1 / value;
            }        
    };

    inline std::ostream& operator<<(std::ostream& out, const Color& v) 
    {
        return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
    }

    inline Color operator+(const Color& u, const Color& v) 
    {
        return Color(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
    }

    inline Color operator-(const Color& u, const Color& v) 
    {
        return Color(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
    }

    inline Color operator*(const Color& u, const Color& v) 
    {
        return Color(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
    }

    inline Color operator*(double t, const Color& v) 
    {
        return Color(t*v.e[0], t*v.e[1], t*v.e[2]);
    }

    inline Color operator*(const Color& v, double t) 
    {
        return t * v;
    }

    inline Color operator/(const Color& v, double t) 
    {
        return (1/t) * v;
    }


    void DrawColor(std::ostream& out, const Color& c);
} // namespace Lazy
