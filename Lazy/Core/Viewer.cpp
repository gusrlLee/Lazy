#include "Core/Viewer.h"

namespace Lazy 
{
    Viewer::Viewer() 
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        mpWindow = glfwCreateWindow(800, 600, "Lazy Physical-Based Rendering", nullptr, nullptr);
        if (!mpWindow) 
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window :-(");
        }

    }
    
    Viewer::~Viewer() 
    {
        glfwTerminate();
    }
}
