#pragma once 

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/Quad.h"

#include "Camera/Camera.h"
#include "Core/Renderer.h"

namespace Lazy 
{
    class Viewer 
    {
        public:
            Viewer(std::shared_ptr<Renderer> pRenderer);
            Viewer(std::shared_ptr<Camera> pCam);
            Viewer(int w, int h);
            ~Viewer();

            void View();
            void View(Color* c);
            bool IsWindowShouldClose() { return glfwWindowShouldClose(mpWindow); }

            void Run();

            void Clear();

            void Update() { 
                glfwSwapBuffers(mpWindow);
                glfwPollEvents(); 
            }

        private:
            void InitGL();
            void DeinitGL();

            // For window 
            GLFWwindow* mpWindow;
            int mWidth, mHeight;

            std::shared_ptr<Shader> mRenderQuadShader;
            std::shared_ptr<Texture> mOut;
            std::shared_ptr<Quad> mQuad;

            std::shared_ptr<Camera> mpCam;
            std::shared_ptr<Renderer> mpRenderer;
    };
}
