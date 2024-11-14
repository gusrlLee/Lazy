#pragma once 

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Lazy 
{
    class Viewer 
    {
        public:
            Viewer();
            ~Viewer();

        private:
            GLFWwindow* mpWindow;
    };
}
