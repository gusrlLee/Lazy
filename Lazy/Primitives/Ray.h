#pragma once 

#include "Math/Vec3.h"
#include "Math/Point3.h"

namespace Lazy 
{
    class Ray 
    {
        public:
            Ray() = default;
            Ray(const Point3 origin, const Vec3& dir) : mOri(origin), mDir(dir) {}

            const Point3& Ori() const { return mOri; }
            const Vec3& Dir() const { return mDir; }

            Point3 At(float t) const { return mOri + t*mDir; }

        private:
            Point3 mOri;
            Vec3 mDir;
    };
}
