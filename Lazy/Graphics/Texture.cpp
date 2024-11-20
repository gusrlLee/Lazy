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
        mPixels = new unsigned char[3 * w * h];

        // setting 
        glGenTextures(1, &mTexID);
        glBindTexture(GL_TEXTURE_2D, mTexID);

        // texture parameter 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        // define data
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pRawData);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, mData);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, mPixels);
    }

    Texture::~Texture()
    {
        delete[] mData;
        delete[] mPixels;
    }

    void Texture::Update(Color* pColor)
    {
        // glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, mData);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, mPixels);
        memcpy(mPixels, pColor, sizeof(Color) * mWidth * mHeight);
    }

    void Texture::Update(unsigned char* pData)
    {
        // glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, mData);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, mPixels);
        memcpy(mPixels, pData, sizeof(unsigned char) * mWidth * mHeight * 3);
    }
}
