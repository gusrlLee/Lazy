#pragma once 

#include "Math/Color.h"

namespace Lazy 
{
    class Frame 
    {
        public:
            Frame() = default;
            Frame(int w, int h);

            void Update();

        private:
            int mWidth;
            int mHeight;
    };
}
