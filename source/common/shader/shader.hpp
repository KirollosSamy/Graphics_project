#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace our
{
    class ShaderProgram
    {

        private:
            // Shader Program Handle (OpenGL object name)
            GLuint program;

        public:
            ShaderProgram()
            {
                // TODO: (Req 1) Create A shader program
                program = glCreateProgram();
            }
            ~ShaderProgram()
            {
                // TODO: (Req 1) Delete a shader program
                glDeleteProgram(program);
            }

            bool attach(const std::string &filename, GLenum type) const;

            bool link() const;

            void use()
            {
                glUseProgram(program);
            }

            GLuint getUniformLocation(const std::string &name)
            {
                // TODO: (Req 1) Return the location of the uniform with the given name
                return glGetUniformLocation(program, name.c_str());
            }

            void set(const std::string &uniform, GLfloat value)
            {
                // TODO: (Req 1) Send the given float value to the given uniform
                glUniform1f(getUniformLocation(uniform), value);
            }

            void set(const std::string &uniform, GLuint value)
            {
                // TODO: (Req 1) Send the given unsigned integer value to the given uniform
                glUniform1ui(getUniformLocation(uniform), value);
            }

            void set(const std::string &uniform, GLint value)
            {
                // TODO: (Req 1) Send the given integer value to the given uniform
                glUniform1i(getUniformLocation(uniform), value);
            }

            void set(const std::string &uniform, glm::vec2 value)
            {
                // TODO: (Req 1) Send the given 2D vector value to the given uniform
                float value_float[2]={value.x,value.y};
                glUniform2fv(getUniformLocation(uniform), 1, value_float);
            }

            void set(const std::string &uniform, glm::vec3 value)
            {
                // TODO: (Req 1) Send the given 3D vector value to the given uniform
                float value_float[3]={value.x,value.y,value.z};
                glUniform3fv(getUniformLocation(uniform), 1, value_float);
            }
            void set(const std::string &uniform, glm::vec4 value)
            {
                // TODO: (Req 1) Send the given 4D vector value to the given uniform
                float value_float[4] = {value.x, value.y, value.z, value.w};
                glUniform4fv(getUniformLocation(uniform), 1, value_float);
            }

            void set(const std::string &uniform, glm::mat4 matrix)
            {
                // TODO: (Req 1) Send the given matrix 4x4 value to the given uniform
                float value_float[16] = {matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3],
                     matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3],
                     matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3],
                     matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3]
                     };
                glUniformMatrix4fv(getUniformLocation(uniform), 1, 0, value_float);
            }
            // TODO: (Req 1) Delete the copy constructor and assignment operator.
            // Question: Why do we delete the copy constructor and assignment operator?
            /**
                Sometimes, it may not make sense for objects of a certain class to be copied.
                For example, if your class manages a resource such as a file handle or network socket,
                copying an object could result in two objects trying to manage the same resource.
                In such cases, you can prevent objects from being copied by deleting the copy constructor.

                When you delete the copy constructor for a class,
                any attempt to create a new object as a copy of an existing object
                will result in a compile-time error. This ensures that objects
                of that class cannot be copied accidentally.
            */
            ShaderProgram(const ShaderProgram &) = delete;
            ShaderProgram &operator=(const ShaderProgram &) = delete;
    };
}
#endif