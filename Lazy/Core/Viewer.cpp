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

        // RenderQuad Vertex Buffer Object 
        mQuad = std::make_shared<Quad>();

        // make output texture 
        mOut = std::make_shared<Texture>(mWidth, mHeight);

        // Define render quad shader 
        mRenderQuadShader = std::make_shared<Shader>("../Lazy/Graphics/ShaderSrc/RenderQuad.vs", "../Lazy/Graphics/ShaderSrc/RenderQuad.fs");

        // for binding texture 
        mRenderQuadShader->Use();
        mRenderQuadShader->SetInt("tex", 0);
    }
    
    Viewer::~Viewer() 
    {
        if (mpWindow)
            glfwDestroyWindow(mpWindow);

        glfwTerminate();
    }

    void Viewer::View()
    {

        Color* c = new Color[mWidth * mHeight];
        memset(c, 128, mWidth * mHeight * sizeof(Color));

        while (!glfwWindowShouldClose(mpWindow))
        {
            mOut->Bind();
            mOut->Update( c );
            
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

            mRenderQuadShader->Use();
            mQuad->Bind();
            mQuad->Draw();

            glfwSwapBuffers(mpWindow);
            glfwPollEvents();
        }

        delete[] c;
    }

    void Viewer::View(Color* c)
    {
        while (!glfwWindowShouldClose(mpWindow))
        {
            mOut->Bind();
            mOut->Update( c );
            
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

            mRenderQuadShader->Use();
            mQuad->Bind();
            mQuad->Draw();

            glfwSwapBuffers(mpWindow);
            glfwPollEvents();
        }
    }
}
