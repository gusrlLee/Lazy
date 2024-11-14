#pragma once 

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Graphics/Shader.h"

namespace Lazy 
{
    class Viewer 
    {
        public:
            Viewer(int w, int h);
            ~Viewer();

            void View();

        private:
            GLFWwindow* mpWindow;
            int mWidth, mHeight;

            std::shared_ptr<Shader> mRenderQuadShader;
    };
}
