#include <iostream>
#include "Lazy/Primitives/Ray.h"
#include "Lazy/Math/Color.h"
#include "Lazy/Camera/Camera.h"

using namespace Lazy;

int main() 
{
    int w = 400;
    int h = 400;

    Camera cam(/* Window width */ w, /* Window height */ h);

    std::cout << "P3\n" << w << ' ' << h << "\n255\n";

    for (int j = 0; j < h; j++)
    {
        std::clog << "\rScanlines remaining : " << (h - j) << ' ' << std::flush;
        for (int i = 0; i < w; i++)
        {
            Ray r = cam.GenRay(i, j);
            Vec3 uDir = UnitVector(r.Dir());
            auto a = 0.5f * (uDir.y() + 1.0f);

            auto color = (1.0f - a) * Color(1.0f, 1.0f, 1.0f) + a * Color(0.5f, 0.7f, 1.0f);
            drawColor(std::cout, color);
        }
    }

    std::clog << "\rDone. \n";
    return 0;
}
