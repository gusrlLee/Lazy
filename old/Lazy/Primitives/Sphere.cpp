#include "Primitives/Sphere.h"
#include "Primitives/Ray.h"
#include "Math/Vec3.h"

namespace Lazy 
{
    Sphere::Sphere(Point3 p, float r) : mPos(p), mRadius(r) {}
    
    bool Sphere::Hit(Ray* r, HitInfo* info)
    {
        
        Vec3 oc = mPos - r->Ori();
        auto a = r->Dir().LengthSqaured();
        auto h = Dot(r->Dir(), oc);
        auto c = oc.LengthSqaured() - mRadius * mRadius;

        auto d = h * h - a * c; 
        if (d < 0) 
        {
            return false;
        }

        auto sqrtd = std::sqrt(d);

        // Find the nearest root that lies in the acceptable range 
        auto root = (h - sqrtd) / a;
        if (root < info->tMin || info->tMax <= root)
        {
            root = (h + sqrtd) / a;
            if (root <= info->tMin || info->tMax <= root)
            {
                return false;
            }
        }

        info->t = root;
        info->p = r->At(info->t);
        info->n = (info->p - mPos) / mRadius;

        return true;
    }

}
