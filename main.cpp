#include <iostream>
#include "Lazy/Primitives/Ray.h"
#include "Lazy/Math/Color.h"


using namespace Lazy;

int main() 
{
    int w = 256;
    int h = 256;

    std::cout << "P3\n" << w << ' ' << h << "\n255\n";
    for (int j = 0; j < h; j++)
    {
        std::clog << "\rScanlines remaining : " << (h - j) << ' ' << std::flush;
        for (int i = 0; i < w; i++)
        {
            auto color = Color(float(i) / (w - 1), float(j)/(h - 1), 0.0f);
            drawColor(std::cout, color);
        }
    }

    return 0;
}
