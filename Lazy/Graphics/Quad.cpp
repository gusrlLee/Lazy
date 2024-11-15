#include "Graphics/Quad.h"

namespace Lazy 
{
    Quad::Quad()
    {
        float quadVertices[] = 
        {
            // positions        // texture Coords
             1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
             1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            -1.0f,  1.0f, 0.0f, 1.0f, 0.0f,
        };

        unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        // Generate buffer object 
        glGenVertexArrays(1, &mQuadVAO);
        glGenBuffers(1, &mQuadVBO);
        glGenBuffers(1, &mQuadEBO);

        // binding 
        glBindVertexArray(mQuadVAO);

        // set vbo
        glBindBuffer(GL_ARRAY_BUFFER, mQuadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

        // set ebo
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mQuadEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }

    Quad::~Quad()
    {
        glDeleteVertexArrays(1, &mQuadVAO);
        glDeleteBuffers(1, &mQuadVBO);
        glDeleteBuffers(1, &mQuadEBO);
    }

    void Quad::Bind()
    {
        glBindVertexArray(mQuadVAO);
    }

    void Quad::Draw()
    {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

}
