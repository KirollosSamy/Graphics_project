#pragma once

#include <glad/gl.h>
#include "vertex.hpp"

namespace our
{

#define ATTRIB_LOC_POSITION 0
#define ATTRIB_LOC_COLOR 1
#define ATTRIB_LOC_TEXCOORD 2
#define ATTRIB_LOC_NORMAL 3

    class Mesh
    {
        // Here, we store the object names of the 3 main components of a mesh:
        // A vertex array object, A vertex buffer and an element buffer
        unsigned int VBO, EBO;
        unsigned int VAO;
        // We need to remember the number of elements that will be draw by glDrawElements
        GLsizei elementCount;

    public:
        // The constructor takes two vectors:
        // - vertices which contain the vertex data.
        // - elements which contain the indices of the vertices out of which each rectangle will be constructed.
        // The mesh class does not keep a these data on the RAM. Instead, it should create
        // a vertex buffer to store the vertex data on the VRAM,
        // an element buffer to store the element data on the VRAM,
        // a vertex array object to define how to read the vertex & element buffer during rendering
        /*
             * This is a function that takes two arguments: a vector of vertices and a vector of elements
             * (indices of vertices that form triangles). It creates a Mesh object from this data and stores it in memory
             * for later use in rendering. The function first stores the number of elements in the elementCount variable for
             * later use in rendering. It then creates a Vertex Array Object (VAO) and binds it. The VAO is used to store
             * vertex data and is required for rendering. The function then creates a Vertex Buffer Object (VBO) and
             * binds it to the GL_ARRAY_BUFFER target. The VBO is used to store vertex data and is used for efficient data
             * transfer between CPU and GPU. The vertex data is then copied to the VBO using glBufferData.
             * The second argument to glBufferData is the size of the data to be copied, which is calculated as
             * the product of the number of vertices and the size of a Vertex struct. The function then configures the position,
             * color, texture coordinate, and normal attributes using glVertexAttribPointer. The attribute locations are specified
             * using constants defined earlier in the code. The third argument to glVertexAttribPointer is the
             * number of components in the attribute (e.g., 3 for position, 4 for color). The fourth argument is the data
             * type of the attribute (e.g., GL_FLOAT for position and normal, GL_UNSIGNED_BYTE for color). The fifth argument
             * is a boolean indicating whether the data should be normalized. The sixth argument is the stride between consecutive
             * attributes, which is equal to the size of a Vertex struct. The seventh argument is the offset of the attribute within
             * the Vertex struct, which is calculated using the offsetof macro. Finally, the function creates an Element Buffer Object
             * (EBO) and binds it to the GL_ELEMENT_ARRAY_BUFFER target. The EBO is used to store the element data,
             * which is the indices of vertices that form triangles. The element data is copied to the EBO using glBufferData.
             * Overall, this function sets up the vertex and element data for rendering by creating and configuring the VAO, VBO, and EBO.
        */
        Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &elements)
        {
            // TODO: (Req 2) Write this function
            //  remember to store the number of elements in "elementCount" since you will need it for drawing
            //  For the attribute locations, use the constants defined above: ATTRIB_LOC_POSITION, ATTRIB_LOC_COLOR, etc

            elementCount = (GLsizei)elements.size();

            // Binding Vertex Array
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            // Configuration Vertex Buffer
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            // Copy vertex data to the buffer
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

            // Configure the position attribute
            GLint positionLoc = ATTRIB_LOC_POSITION;
            glEnableVertexAttribArray(positionLoc);
            glVertexAttribPointer(positionLoc, 3, GL_FLOAT, false, sizeof(Vertex), (void *)offsetof(Vertex, position));

            // Configure the color attribute
            GLint colorLoc = ATTRIB_LOC_COLOR;
            glEnableVertexAttribArray(colorLoc);
            glVertexAttribPointer(colorLoc, 4, GL_UNSIGNED_BYTE, true, sizeof(Vertex), (void *)offsetof(Vertex, color));

            // Configure the texture coordinate attribute
            GLint textCoordLoc = ATTRIB_LOC_TEXCOORD;
            glEnableVertexAttribArray(textCoordLoc);
            glVertexAttribPointer(textCoordLoc, 2, GL_FLOAT, false, sizeof(Vertex), (void *)offsetof(Vertex, tex_coord));

            // Configure the normal attribute
            GLint normalLoc = ATTRIB_LOC_NORMAL;
            glEnableVertexAttribArray(normalLoc);
            glVertexAttribPointer(normalLoc, 3, GL_FLOAT, false, sizeof(Vertex), (void *)offsetof(Vertex, normal));

            // Binding Elements Buffer
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

            // Copy element data to the buffer
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount * sizeof(unsigned int), elements.data(), GL_STATIC_DRAW);
        }

        // this function should render the mesh
        void draw()
        {
            // TODO: (Req 2) Write this function
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, (void *)0);
             glBindVertexArray(0);
        }

        // this function should delete the vertex & element buffers and the vertex array object
        ~Mesh()
        {
            // TODO: (Req 2) Write this function
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
            
        }

        Mesh(Mesh const &) = delete;
        Mesh &operator=(Mesh const &) = delete;
    };

}
