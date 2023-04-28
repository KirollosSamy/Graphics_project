#pragma once

#include <glad/gl.h>
#include <json/json.hpp>
#include <glm/vec4.hpp>

namespace our
{

    // This class defined an OpenGL sampler
    class Sampler
    {
        // The OpenGL object name of this sampler
        GLuint name;

    public:
        // This constructor creates an OpenGL sampler and saves its object name in the member variable "name"
        Sampler()
        {

            // TODO: (Req 6) Complete this function
            //  generate sampler and save it in name variable
            //  which are used to specify how textures are sampled in an OpenGL program
            //  1--->stands for one sampler object

            glGenSamplers(1, &name);
        };

        // This deconstructor deletes the underlying OpenGL sampler
        ~Sampler()
        {
            // TODO: (Req 6) Complete this function
            //  delete the sampler (name)
            glDeleteSamplers(1, &name);
        }

        // This method binds this sampler to the given texture unit
        void bind(GLuint textureUnit) const
        {
            // TODO: (Req 6) Complete this function
            // The texture unit number should be a value between 0 and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1.
            // bind the sampler to textureUnit-->0 or 1 or 2 ...
            glBindSampler(textureUnit, name);
        }

        // This static method ensures that no sampler is bound to the given texture unit
        static void unbind(GLuint textureUnit)
        {
            // TODO: (Req 6) Complete this function

            // In this implementation, we simply call glBindSampler with the texture unit set to textureUnit and the sampler set to 0, which unbinds any sampler that was previously bound to that texture unit.
            glBindSampler(textureUnit, 0);
        }

        // This function sets a sampler paramter where the value is of type "GLint"
        // This can be used to set the filtering and wrapping parameters

        // Filtering parameters control how texels (texture pixels) are sampled when a texture coordinate falls between texels, while wrapping parameters control how texture coordinates outside the range of [0, 1] are handled.
        // For example, GL_TEXTURE_WRAP_S and GL_TEXTURE_WRAP_T are wrapping parameters that control how texture coordinates outside the range of [0, 1] are handled in the s and t directions, respectively. The possible values for these parameters are GL_REPEAT, GL_CLAMP_TO_EDGE, and GL_MIRRORED_REPEAT.
        // Similarly, GL_TEXTURE_MIN_FILTER and GL_TEXTURE_MAG_FILTER are filtering parameters that control how texels are sampled when the texture is minified (shrunk) or magnified (enlarged), respectively. The possible values for these parameters are GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, and GL_LINEAR_MIPMAP_LINEAR.
        void set(GLenum parameter, GLint value) const
        {
            // TODO: (Req 6) Complete this function
            //  like : glSamplerParameteri(color_sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glSamplerParameteri(name, parameter, value);
        }

        // This function sets a sampler paramter where the value is of type "GLfloat"
        // This can be used to set the "GL_TEXTURE_MAX_ANISOTROPY_EXT" parameter

        // This parameter controls the amount of anisotropic filtering that is applied to the texture. Anisotropic filtering is a technique that improves the quality of textures when they are viewed at oblique angles by reducing the blurriness and improving the clarity of the texture.
        // The GL_TEXTURE_MAX_ANISOTROPY_EXT parameter specifies the maximum degree of anisotropy to be used when filtering the texture.
        void set(GLenum parameter, GLfloat value) const
        {
            // TODO: (Req 6) Complete this function
            glSamplerParameterf(name, parameter, value);
        }

        // This function sets a sampler paramter where the value is of type "GLfloat[4]"
        // This can be used to set the "GL_TEXTURE_BORDER_COLOR" parameter

        // This parameter specifies the color that is used for texture borders when the texture is accessed using texture coordinates that fall outside the range of [0,1].
        // The value of this parameter is a four-component floating-point vector that specifies the red, green, blue, and alpha components of the border color.
        void set(GLenum parameter, glm::vec4 value) const
        {
            glSamplerParameterfv(name, parameter, &(value.r));
        }

        // Given a json object, this function deserializes the sampler state
        void deserialize(const nlohmann::json &data);

        Sampler(const Sampler &) = delete;
        Sampler &operator=(const Sampler &) = delete;
    };

}