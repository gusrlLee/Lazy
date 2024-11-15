#pragma once 

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/Quad.h"

namespace Lazy 
{
    class Viewer 
    {
        public:
            Viewer(int w, int h);
            ~Viewer();

            void View();
            void View(Color* c);

        private:
            GLFWwindow* mpWindow;
            int mWidth, mHeight;

            std::shared_ptr<Shader> mRenderQuadShader;
            std::shared_ptr<Texture> mOut;
            std::shared_ptr<Quad> mQuad;
    };
}
