#include "Core/Frame.h"

namespace Lazy
{
    Frame::Frame(int w, int h)
    {
        mWidth = w; 
        mHeight = h; 
        mpData = new Color[w * h];
        mpPixels = new unsigned char[3 * w * h];
    }

    Frame::~Frame()
    {
        delete[] mpData;
        delete[] mpPixels;
    }
}
