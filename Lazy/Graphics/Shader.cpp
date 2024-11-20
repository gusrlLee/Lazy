#include "Graphics/Shader.h"

namespace Lazy 
{
    Shader::Shader(const char* vsPath, const char* fsPath)
    {
        std::string vsCode, fsCode;
        std::ifstream vsFile, fsFile;

        vsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try 
        {
            vsFile.open(vsPath);
            fsFile.open(fsPath);

            std::stringstream vsStream, fsStream;
            vsStream << vsFile.rdbuf();
            fsStream << fsFile.rdbuf();

            vsFile.close();
            fsFile.close();

            vsCode = vsStream.str();
            fsCode = fsStream.str();
        } 
        catch (std::ifstream::failure& e)
        {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: "  << e.what() << "\n";
        }

        const char* vsc = vsCode.c_str();
        const char* fsc = fsCode.c_str();

        unsigned int vs, fs;

        // vertex shader compile
        vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vsc, nullptr);
        glCompileShader(vs);
        Check(vs, "VERTEX");

        // fragment shader compile
        fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fsc, nullptr);
        glCompileShader(fs);
        Check(vs, "FRAGMENT");

        // create shader program 
        mID = glCreateProgram(); 
        glAttachShader(mID, vs);
        glAttachShader(mID, fs);
        glLinkProgram(mID);
        Check(mID, "PROGRAM");

        glDeleteShader(vs);
        glDeleteShader(fs);

        std::clog << "Success to create RenderQuad Shader Program! :-)\n";
    }

    Shader::~Shader() {}

    void Shader::Check(unsigned int shader, std::string sType)
    {
        int success;
        char infoLog[1024];
        if (sType != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of sType: " << sType << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of sType: " << sType << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }

    }
}
