#include "Math/Color.h"

namespace Lazy
{
    Color::Color() : e{0, 0, 0} {}

    Color::Color(Vec3 v) 
    {
        auto r = v.x();
        auto g = v.y();
        auto b = v.z();
    
        e[0] = int(255.999 * r);
        e[1] = int(255.999 * g);
        e[2] = int(255.999 * b);
    }

    Color::Color(unsigned char value) : e{value, value, value} {}
    Color::Color(unsigned char e1, unsigned char e2, unsigned char e3) : e{e1, e2, e3} {}

    void DrawColor(std::ostream& out, const Color& c) 
    {
    
        out << (int)c[0] << ' ' << (int)c[1] << ' ' << (int)c[2] << '\n';
    }
}
