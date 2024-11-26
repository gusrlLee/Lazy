#pragma once
#include "vec3.h"

namespace lazy
{
    class ray
    {
    public:
        ray();
        ray(const point3 &o, const vec3 &d);

        const point3& origin() const { return m_orig; }
        const vec3& dir() const { return m_dir; }
        point3 at(double t) const 
        {
            return m_orig + t * m_dir;
        }

    private:
        const point3 m_orig;
        const vec3 m_dir;
    };
}