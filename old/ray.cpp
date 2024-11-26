#include "ray.h"

namespace lazy 
{
    ray::ray() {}
    ray::ray(const point3 &o, const vec3 &d) : m_orig(o), m_dir(d) {} 

}