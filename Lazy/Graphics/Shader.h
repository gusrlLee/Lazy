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

            void SetBool(const std::string &name, bool v) const 
            {
                glUniform1i(glGetUniformLocation(mID, name.c_str()), (int)v); 
            }

            void SetInt(const std::string &name, int v) const 
            {
                glUniform1i(glGetUniformLocation(mID, name.c_str()), v);
            }

            void SetFloat(const std::string &name, float v) const 
            {
                glUniform1f(glGetUniformLocation(mID, name.c_str()), v);  
            }

        private:
            void Check(unsigned int shader, std::string sType);
            unsigned int mID;
    };
}
