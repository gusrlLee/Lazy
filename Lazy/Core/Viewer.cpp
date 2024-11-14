#include "Core/Viewer.h"

namespace Lazy 
{
    Viewer::Viewer(int w, int h) 
    {
        mWidth = w;
        mHeight = h;

        // GLFW init
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        mpWindow = glfwCreateWindow(w, h, "Lazy Physical-Based Rendering", nullptr, nullptr);
        if (!mpWindow) 
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window :-(");
        }

        glfwMakeContextCurrent(mpWindow);

        // GLAD init
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            glfwTerminate();
            throw std::runtime_error("Failed to init GLAD library :-(");
        }

        if (glfwExtensionSupported("GL_ARB_pixel_buffer_object"))
        {
            glfwTerminate();
            throw std::runtime_error("[ERROR] current device not support GL_ARB_pixel_buffer_object! :-(");
        }

        // Define render quad shader 
        mRenderQuadShader = std::make_shared<Shader>("../Lazy/Graphics/ShaderSrc/RenderQuad.vs", "../Lazy/Graphics/ShaderSrc/RenderQuad.fs");
    }
    
    Viewer::~Viewer() 
    {
        if (mpWindow)
            glfwDestroyWindow(mpWindow);

        glfwTerminate();
    }

    void Viewer::View()
    {
        while (!glfwWindowShouldClose(mpWindow))
        {
            glfwSwapBuffers(mpWindow);
            glfwPollEvents();
        }
    }
}
