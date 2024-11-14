#pragma once 

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "glad/glad.h"

namespace Lazy 
{
    class Shader 
    {
        public:
            Shader(const char* vsPath, const char* fsPath);
            ~Shader() = default;

            void Use()
            {
                glUseProgram(mID);
            }

            void SetBool(const std::string &name, bool v) const {}
            void SetInt(const std::string &name, int v) const {}
            void SetFloat(const std::string &name, float v) const {}

        private:
            void Check(unsigned int shader, std::string sType);
            unsigned int mID;
    };
}
