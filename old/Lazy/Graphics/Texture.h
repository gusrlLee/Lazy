#pragma once 

#include "glad/glad.h"

#include "Math/Color.h"

namespace Lazy 
{
    class Texture 
    {
        public:
            Texture(int w, int h);
            ~Texture();

            void Update(Color* pColor);
            void Update(unsigned char* pData);

            void Bind() const 
            {
                glBindTexture(GL_TEXTURE_2D, mTexID);
            }

        private:
            unsigned int mTexID;
            int mWidth, mHeight;
            Color* mData;
            unsigned char* mPixels;
    };

}

/* MAKE TEXTURE CODE 
#include <iostream>
#include <vector>

class Color 
{
    public:
        Color() : e{255, 0, 0} {}
        unsigned char e[3];
};
    

int main()
{
    std::cout<<"Hello World";
    Color* color = new Color[5];
    std::vector<Color> data(5);
    
    unsigned char* ptr = reinterpret_cast<unsigned char*>(color);
    
    for (int i=0; i<5 * 3; i++)
    {
        std::cout << "index " << i << " value : " << (int)ptr[i] << std::endl;
    }
    return 0;
}
*/
