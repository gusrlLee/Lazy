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
