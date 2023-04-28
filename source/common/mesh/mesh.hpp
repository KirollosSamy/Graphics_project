#pragma once

#include <glad/gl.h>
#include "vertex.hpp"
#include <GLFW/glfw3.h>
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
        Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &elements)
        {
            elementCount = elements.size();

            // TODO: (Req 2) Write this function
            //  remember to store the number of elements in "elementCount" since you will need it for drawing
            //  For the attribute locations, use the constants defined above: ATTRIB_LOC_POSITION, ATTRIB_LOC_COLOR, etc

            // the element buffer (EBO) identify the order of the vertices but the data is in the vertex buffer (VBO)

            // The glBindBuffer function binds the buffer object with the specified name to the specified buffer target.
            // In this case, it binds the VBO to the GL_ARRAY_BUFFER target and the EBO to the GL_ELEMENT_ARRAY_BUFFER target.
            // to make it know that iam talking about this VBO and EBO

            // The glBufferData function creates and initializes a buffer object's data store.
            // It takes the buffer target, the size of the data in bytes, a pointer to the data.

            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(unsigned int), elements.data(), GL_STATIC_DRAW);

            // bind the vertex array
            // to bind the vertex array with the vertex buffer
            //  we want to declare that this vertex array which will read from the buffers and send to the vertex shader
            // The glBindVertexArray function binds the specified vertex array object.

            // glBindBuffer(GL_ARRAY_BUFFER, VBO);

            // this the position which the vertex shader will read from
            // glVertexAttribPointer--> this to make it understand how to read the bits
            // i gave it the position and 3 as they are three dimensions and the size to know how to jump to the another element
            // this to change the data from c++ not from the vertex shader , i can change the position from here.
            //  The glEnableVertexAttribArray function enables the generic vertex attribute array specified by position_loc, color_loc, texture_loc, and normal_loc.
            GLint position_loc = ATTRIB_LOC_POSITION;
            glEnableVertexAttribArray(position_loc);
            glVertexAttribPointer(position_loc, 3, GL_FLOAT, false, sizeof(Vertex), 0);

            // 4 as red blue green alpha not 3 as the positions x y z
            // the last parameter --> to know where to start the color , it is not from zero like the position but it is the offsetof (vertex ,color) , how many step to move in the vertex struct to get the color
            // GL_UNSIGNED_BYTE , the type of the color
            // normalized (true) to get the max 255 and divide all by it  before sending to the vertex shader
            GLint color_loc = ATTRIB_LOC_COLOR;
            glEnableVertexAttribArray(color_loc);
            glVertexAttribPointer(color_loc, 4, GL_UNSIGNED_BYTE, true, sizeof(Vertex), (void *)offsetof(Vertex, color));

            // we set up the texture coordinate vertex attribute for the shader program.
            // 2---> for texture coordinates (x,y)-->2D texture
            GLint texture_loc = ATTRIB_LOC_TEXCOORD;
            glEnableVertexAttribArray(texture_loc);
            glVertexAttribPointer(texture_loc, 2, GL_FLOAT, false, sizeof(Vertex), (void *)offsetof(Vertex, tex_coord));

            // sets up the normal vector vertex attribute for the shader program.
            // 3---> for normal vector components (X,y,z)
            GLint normal_loc = ATTRIB_LOC_NORMAL;
            glEnableVertexAttribArray(normal_loc);
            glVertexAttribPointer(normal_loc, 3, GL_FLOAT, true, sizeof(Vertex), (void *)offsetof(Vertex, normal));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        }
        void draw()
        {
            // this function should render the mesh
            // it is very important to bind the vertex array before drawing to record it
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);
            // TODO: (Req 2) Write this function
        }

        // this function should delete the vertex & element buffers and the vertex array object
        ~Mesh()
        {
            // TODO: (Req 2) Write this function
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
            glDeleteVertexArrays(1, &VAO);
        }

        Mesh(Mesh const &) = delete;
        Mesh &operator=(Mesh const &) = delete;
    };

}