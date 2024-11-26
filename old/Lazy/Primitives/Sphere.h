#pragma once 

#include "Math/Vec3.h"
#include "Math/Point3.h"

#include "Primitives/Primitive.h"

namespace Lazy 
{
    class Sphere : public Primitive 
    {
        public:
            Sphere() = default;
            Sphere(Point3 p, float r);
            bool Hit(Ray* r, HitInfo* info) override;

        private:
            Point3 mPos;
            float mRadius;
    };
}
