#pragma once 

#include "Math/Color.h"

namespace Lazy 
{
    class Frame
    {
        public:
            Frame(int w, int h);
            ~Frame();

            Color* GetPixels() { return mpData; }
            int GetWidth() { return mWidth; }
            int GetHeight() { return mHeight; }

            Color* mpData;
            int mWidth, mHeight;
            unsigned char* mpPixels;
            
        private:


    };
}
