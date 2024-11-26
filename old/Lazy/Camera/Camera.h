#pragma once 
#include "Math/Point3.h"
#include "Primitives/Ray.h"

namespace Lazy 
{
    class Camera 
    {
        public:
            Camera() = default;
            Camera(int width, int height);

            Point3 GetPos() const { return mPos; }
            Vec3 GetDir() const { return mDir; }

            Ray GenRay(int x, int y);

        private:
            int mWinWidth;
            int mWinHeight;

            float mRatio = 1.0;

            Point3 mPos;
            Vec3 mDir;
            
            Point3 mLoc; // Left-Top
            Vec3 dU;
            Vec3 dV;
    };
}
