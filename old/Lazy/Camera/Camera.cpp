#include "Camera/Camera.h"

namespace Lazy 
{
    Camera::Camera(int width, int height) : mRatio(1.0f), mWinWidth(width)
    {
        // aspect ratio
        mRatio = 1.0f;

        // Window setting 
        mWinWidth = width;
        mWinHeight = int(width / mRatio);
        mWinHeight = (mWinHeight < 1) ? 1 : mWinHeight;
        
        // Camera Center 
        mPos = Vec3(0.0f);

        // focal length
        auto focalLen = 1.0f;
        
        // view port 
        auto vPortHeight = 2.0f;
        auto vPortWidth = vPortHeight * (float(mWinWidth) / mWinHeight);

        auto vU = Vec3(vPortWidth, 0.0f, 0.0f);
        auto vV = Vec3(0.0f, -vPortHeight, 0.0f);

        // delta view port U,V value 
        dU = vU / mWinWidth;
        dV = vV / mWinHeight;
        auto vUpperLeft = mPos - Vec3(0.0f, 0.0f, focalLen) - vU / 2 - vV / 2;

        // left-top start point 
        mLoc = vUpperLeft + 0.5f * (dU + dV);
    }

    Ray Camera::GenRay(int x, int y)
    {
        // calc ray info
        auto pixelCenter = mLoc + (x * dU) + (y * dV);
        auto rOri = mPos;
        auto rDir = pixelCenter - mPos;

        return Ray(rOri, rDir);
    }

}
