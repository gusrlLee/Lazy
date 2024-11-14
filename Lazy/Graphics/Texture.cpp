#include <memory>

#include "Graphics/Texture.h"
#include "Math/Color.h"

namespace Lazy 
{
    Texture::Texture(int w, int h)
    {
        mWidth = w;
        mHeight = h;
        mData = new Color[w * h];
        unsigned char* pRawData = reinterpret_cast<unsigned char*>(mData);

        glGenTextures(1, &mTexID);
        glBindTexture(GL_TEXTURE_2D, mTexID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, mData);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::~Texture()
    {
        delete mData;
    }

    void Texture::Update(Color* pColor)
    {
        memcpy(mData, pColor, sizeof(Color) * mWidth * mHeight);
    }
}
