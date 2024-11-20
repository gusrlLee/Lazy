#include "Core/Viewer.h"
#include "Core/Frame.h"

namespace Lazy
{
    int i = 0;
    Viewer::Viewer(std::shared_ptr<Renderer> pRenderer)
    {
        mpRenderer = pRenderer;

        mWidth = pRenderer->GetWidth();
        mHeight = pRenderer->GetHeight();

        InitGL();

        // RenderQuad Vertex Buffer Object
        mQuad = std::make_shared<Quad>();
        // make output texture
        mOut = std::make_shared<Texture>(mWidth, mHeight);
        // Define render quad shader
        mRenderQuadShader = std::make_shared<Shader>(
            /* vertex shader */ "../Lazy/Graphics/ShaderSrc/RenderQuad.vs",
            /* fragment shader */ "../Lazy/Graphics/ShaderSrc/RenderQuad.fs");

        // for binding texture
        mRenderQuadShader->Use();
        mRenderQuadShader->SetInt("tex", 0);
    }

    Viewer::Viewer(std::shared_ptr<Camera> pCam) {}

    Viewer::Viewer(int w, int h)
    {
        mWidth = w;
        mHeight = h;
        InitGL();

        // RenderQuad Vertex Buffer Object
        mQuad = std::make_shared<Quad>();
        // make output texture
        mOut = std::make_shared<Texture>(mWidth, mHeight);
        // Define render quad shader
        mRenderQuadShader = std::make_shared<Shader>(
            /* vertex shader */ "../Lazy/Graphics/ShaderSrc/RenderQuad.vs",
            /* fragment shader */ "../Lazy/Graphics/ShaderSrc/RenderQuad.fs");

        // for binding texture
        mRenderQuadShader->Use();
        mRenderQuadShader->SetInt("tex", 0);
    }

    Viewer::~Viewer()
    {
        DeinitGL();
    }

    void Viewer::View()
    {
        Color *c = new Color[mWidth * mHeight];

        i++;
        i = (i % 255);
        memset(c, i, mWidth * mHeight * sizeof(Color));

        mOut->Bind();
        mOut->Update(c);

        mRenderQuadShader->Use();
        mQuad->Bind();
        mQuad->Draw();

        delete[] c;
    }

    void Viewer::Run()
    {
        Frame* pFrame = new Frame(mWidth, mHeight);
        auto pFrame2 = std::make_shared<Frame>(mWidth, mHeight);
        
        while (!glfwWindowShouldClose(mpWindow))
        {
            this->Clear();

            mpRenderer->Render(pFrame2);
            mOut->Bind();
            mOut->Update(pFrame2->mpPixels);

            mRenderQuadShader->Use();
            mQuad->Bind();
            mQuad->Draw();
            
            this->Update();
        }

        delete pFrame;
    }

    void Viewer::View(Color* c)
    {
        mOut->Bind();
        mRenderQuadShader->Use();
        mQuad->Bind();
        mQuad->Draw();
    }

    void Viewer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    }

    void Viewer::InitGL()
    {
        // GLFW init
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        mpWindow = glfwCreateWindow(mWidth, mHeight, "Lazy Physical-Based Rendering", nullptr, nullptr);
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
    }

    void Viewer::DeinitGL()
    {
        glfwDestroyWindow(mpWindow);
        glfwTerminate();
    }
}
