#pragma once 
#include <iostream>
#include <string>

#include "glad/glad.h"

namespace Lazy 
{
    class Quad
    {
        public:
            Quad();
            ~Quad();
            void Bind();
            void Draw();

        private:
            unsigned int mQuadVAO;
            unsigned int mQuadVBO;
            unsigned int mQuadEBO;
    };
}
