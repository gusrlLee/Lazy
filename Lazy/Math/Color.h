#pragma once 
#include "Math/Vec3.h"

namespace Lazy 
{
    using Color = Vec3;

    void drawColor(std::ostream& out, const Color& c) 
    {
        auto r = c.x();
        auto g = c.y();
        auto b = c.z();

        int rByte = int(255.999 * r);
        int gByte = int(255.999 * g);
        int bByte = int(255.999 * b);

        out << rByte << ' ' << gByte << ' ' << bByte << '\n';
    }
}
