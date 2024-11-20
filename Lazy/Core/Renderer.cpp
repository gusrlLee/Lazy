#include "Core/Renderer.h"
#include "Core/Frame.h"
#include "Math/Color.h"
#include "Camera/Camera.h"

namespace Lazy 
{
    Renderer::Renderer(std::shared_ptr<Camera> pCam)
    {
        mWidth = -1;
        mHeight = -1;
        i = 0;
        mpCam = pCam;
    }

    Renderer::~Renderer()
    {

    }

    void Renderer::SetCam(std::shared_ptr<Camera> cam)
    {

    }

    void Renderer::Render(std::shared_ptr<Frame> pFrame)
    {
        i++;
        i = (i % 255);
        for (int y = 0; y < mHeight; y++ )
        {
            for (int x = 0; x < mWidth; x++)
            {
                pFrame->mpPixels[3 * (mWidth * y + x) + 0] = i;
                pFrame->mpPixels[3 * (mWidth * y + x) + 1] = i;
                pFrame->mpPixels[3 * (mWidth * y + x) + 2] = i;
            }
        }
    }

    void Renderer::Render(Frame* pFrame)
    {
        i++;
        i = (i % 255);
        memset(pFrame->mpData, i, sizeof(Color) * pFrame->GetWidth() * pFrame->GetWidth());
    }
}
