#include <iostream>
#include <string.h>
#include <getopt.h>
#include <cmath>

#include "color.h"
#include "vec3.h"
#include "ray.h"

double hit_sphere(const lazy::point3& center, double radius, const lazy::ray& r)
{
    lazy::vec3 oc = center - r.origin();
    auto a = r.dir().length_squared();
    auto h = lazy::dot(r.dir(), oc);
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = h * h - a * c;

    if (discriminant < 0.0) 
    {
        return -1.0;
    }
    else 
    {
        return (h - std::sqrt(discriminant)) / a;
    }
}

lazy::color ray_color(const lazy::ray& r)
{
    auto t = hit_sphere(lazy::point3(0, 0, -1), 0.5, r);
    if (t > 0.0) 
    {
        lazy::vec3 n = lazy::unit_vector(r.at(t) - lazy::vec3(0.0, 0.0, -1.0));
        return 0.5 * lazy::color( n.x() + 1.0, n.y() + 1.0, n.z() + 1.0 );
    }
    
    lazy::vec3 unit_dir = lazy::unit_vector(r.dir());
    auto a = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - a) * lazy::color(1.0, 1.0, 1.0) + a * lazy::color(0.5, 0.7, 1.0);
}

void Help()
{
    std::clog << "Hello world!\n";
    std::clog << "-w, --width           Set window width (default = 1080)\n";
    std::clog << "-w, --width           Set window height (default = 720)\n";
    std::clog << "-v, --view-mode       Set view mode\n";
}

int main(int argc, char **argv)
{
    int opt;
    int w = 1080;
    int h = 720;

    auto aspect_ratio = 16.0 / 9.0;
    auto image_width = 400;

    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // camera setting 
    auto focal_length = 1.0f;
    auto viewport_height = 2.0f;
    auto viewport_width = viewport_height * (float(image_width) / image_height);
    auto camera_center = lazy::point3(0.0, 0.0, 0.0);

    auto viewport_u = lazy::vec3(viewport_width, 0.0, 0.0);
    auto viewport_v = lazy::vec3(0.0, -viewport_height, 0.0);

    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = camera_center - lazy::vec3(0.0, 0.0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel100_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++)
    {
        std::clog << "\rScanlines remaining : " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            auto pixel_center = pixel100_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto d = pixel_center - camera_center;
            lazy::ray r(pixel_center, d);

            lazy::color pixel_color = ray_color(r);
            lazy::write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone. \n";

#if 0 
    // main 
    auto pCam = std::make_shared<Camera>(/* Window width*/ w, /* Window height */ h);

    // Renderer setting 
    auto pRenderer = std::make_shared<Renderer>(pCam);
    pRenderer->SetWidth(w);
    pRenderer->SetHeight(h);

    auto view = std::make_shared<Viewer>(pRenderer);
    view->Run();
#endif

#if 0
    // VIEW MODE 
    if (vMode)
    {
        auto view = std::make_shared<Viewer>(w, h);
        auto pRenderer = std::make_shared<Renderer>(cam);
        Frame* pFrame = new Frame(w, h);

        while (!view->IsWindowShouldClose())
        {
            pRenderer->Render(pFrame);
            view->View(pFrame->GetPixels());
        }

        delete pFrame;
    }
    else // SAVE MODE 
    {
        std::cout << "P3\n" << w << ' ' << h << "\n255\n";

        for (int j = 0; j < h; j++)
        {
            std::clog << "\rScanlines remaining : " << (h - j) << ' ' << std::flush;
            for (int i = 0; i < w; i++)
            {
                Ray r = cam->GenRay(i, j);
                Vec3 uDir = UnitVector(r.Dir());
                auto a = 0.5f * (uDir.y() + 1.0f);

                auto fColor = (1.0f - a) * Vec3(1.0f, 1.0f, 1.0f) + a * Vec3(0.5f, 0.7f, 1.0f);
                auto color = Color(fColor);

                DrawColor(std::cout, color);
            }
        }

        std::clog << "\rDone. \n";
        WriteRenderImage("output.png");
    }
#endif
    return 0;
}


//    std::string fName = "output.png";
//     bool vMode = false;

//     // options
//     const struct option lOptions[] =
//         {
//             {"help", no_argument, nullptr, 'H'},
//             {"width", required_argument, nullptr, 'w'},
//             {"height", required_argument, nullptr, 'h'},
//             {"view-mode", no_argument, nullptr, 'v'},
//             {nullptr, 0, nullptr, 0},
//         };

//     while ((opt = getopt_long(argc, argv, "Hw:h:v", lOptions, nullptr)) != -1)
//     {
//         switch (opt)
//         {
//         case 'H':
//             Help();
//             break;
//         case 'w':
//             w = std::atoi(optarg);
//             std::clog << "window width = " << w << std::endl;
//             break;
//         case 'h':
//             h = std::atoi(optarg);
//             std::clog << "window height = " << h << std::endl;
//             break;
//         case 'v':
//             vMode = true;
//             break;
//         default:
//             Help();
//             return -1;
//         }
//     }