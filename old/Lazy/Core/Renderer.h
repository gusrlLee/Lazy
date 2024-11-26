#pragma once 

#include <iostream>

namespace Lazy 
{
    class Frame;
    class Camera;

    class Renderer 
    {
        public:
            Renderer(std::shared_ptr<Camera> pCam);
            ~Renderer();

            void SetCam(std::shared_ptr<Camera> cam);
            void SetWidth(int width) { mWidth = width; }
            void SetHeight(int height) { mHeight = height; }

            int GetWidth() { return mWidth; }
            int GetHeight() { return mHeight; }

            // Main Render Function 
            void Render(std::shared_ptr<Frame> pFrame);
            void Render(Frame* pFrame);

        private:
            int mWidth, mHeight;
            int i;
            std::shared_ptr<Camera> mpCam;
    };
}
