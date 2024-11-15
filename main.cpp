#include <iostream>
#include <string.h>
#include <getopt.h>

#include "Lazy/Core/Viewer.h"
#include "Lazy/Primitives/Ray.h"
#include "Lazy/Math/Color.h"
#include "Lazy/Camera/Camera.h"

using namespace Lazy;

void Help() 
{
    std::clog << "Hello world!\n";
    std::clog << "-w, --width           Set window width (default = 1080)\n";
    std::clog << "-w, --width           Set window height (default = 720)\n";
    std::clog << "-v, --view-mode       Set view mode\n";
}

int main(int argc, char** argv) 
{
    int opt;
    int w = 1080;
    int h = 720;
    std::string fName = "output.png";
    bool vMode = false;

    // options 
    const struct option lOptions[] = 
    {
        {"help", no_argument, nullptr, 'H'},
        {"width", required_argument, nullptr, 'w'},
        {"height", required_argument, nullptr, 'h'},
        {"view-mode", no_argument, nullptr, 'v'},
        {nullptr, 0, nullptr, 0},
    };

    while ((opt = getopt_long(argc, argv, "Hw:h:v", lOptions, nullptr)) != -1)
    {
        switch (opt)
        {
            case 'H': 
                Help();
                break;
            case 'w':
                w = std::atoi(optarg);
                std::clog << "window width = " << w << std::endl;
                break;
            case 'h':
                h = std::atoi(optarg);
                std::clog << "window height = " << h << std::endl;
                break;
            case 'v':
                vMode = true;
                break;
            default:
                Help();
                return -1;
        }
    }

    Camera cam(/* Window width */ w, /* Window height */ h);

    if (vMode)
    {
        Color* pColor = new Color[w * h];
        for (int j = 0; j < h; j++)
        {
            for (int i = 0; i < w; i++)
            {
                Ray r = cam.GenRay(i, j);
                Vec3 uDir = UnitVector(r.Dir());
                auto a = 0.5f * (uDir.y() + 1.0f);

                auto fColor = (1.0f - a) * Vec3(1.0f, 1.0f, 1.0f) + a * Vec3(0.5f, 0.7f, 1.0f);
                pColor[w * j + i] = Color(fColor);

            }
        }

        auto view = std::make_shared<Viewer>(w, h);
        view->View(pColor);
        delete[] pColor;
    }
    else 
    {
        std::cout << "P3\n" << w << ' ' << h << "\n255\n";

        for (int j = 0; j < h; j++)
        {
            std::clog << "\rScanlines remaining : " << (h - j) << ' ' << std::flush;
            for (int i = 0; i < w; i++)
            {
                Ray r = cam.GenRay(i, j);
                Vec3 uDir = UnitVector(r.Dir());
                auto a = 0.5f * (uDir.y() + 1.0f);

                auto fColor = (1.0f - a) * Vec3(1.0f, 1.0f, 1.0f) + a * Vec3(0.5f, 0.7f, 1.0f);
                auto color = Color(fColor);

                DrawColor(std::cout, color);
            }
        }

        std::clog << "\rDone. \n";
    }

    return 0;
}
