#pragma once

#include <glad/gl.h>
#include <glm/vec4.hpp>
#include <json/json.hpp>

namespace our {
    // There are some options in the render pipeline that we cannot control via shaders
    // such as blending, depth testing and so on
    // Since each material could require different options (e.g. transparent materials usually use blending),
    // we will encapsulate all these options into a single structure that will also be responsible for configuring OpenGL's pipeline
    struct PipelineState {
        // This set of pipeline options specifies whether face culling will be used or not and how it will be configured
        struct {
            bool enabled = false;
            GLenum culledFace = GL_BACK;
            GLenum frontFace = GL_CCW;
        } faceCulling;

        // This set of pipeline options specifies whether depth testing will be used or not and how it will be configured
        struct {
            bool enabled = false;
            GLenum function = GL_LEQUAL;
        } depthTesting;

        // This set of pipeline options specifies whether blending will be used or not and how it will be configured
        struct {
            bool enabled = false;
            GLenum equation = GL_FUNC_ADD;
            GLenum sourceFactor = GL_SRC_ALPHA;
            GLenum destinationFactor = GL_ONE_MINUS_SRC_ALPHA;
            glm::vec4 constantColor = {0, 0, 0, 0};
        } blending;

        // These options specify the color and depth mask which can be used to
        // prevent the rendering/clearing from modifying certain channels of certain targets in the framebuffer
        glm::bvec4 colorMask = {true, true, true, true}; // To know how to use it, check glColorMask
        bool depthMask = true; // To know how to use it, check glDepthMask

        //i check it but didn't get the idea behind(the how to use)


        // This function should set the OpenGL options to the values specified by this structure
        // For example, if faceCulling.enabled is true, you should call glEnable(GL_CULL_FACE), otherwise, you should call glDisable(GL_CULL_FACE)
        void setup() const {
            //TODO: (Req 4) Write this function
            // Enable or disable face culling based on the value of faceCulling.enabled

            //face culling refers to the process of determining which faces
            //of a three-dimensional object are visible or hidden from a particular viewpoint.
            if (faceCulling.enabled) {
                glEnable(GL_CULL_FACE);
                //Once enabled, you can specify which faces should
                //be culled and the order in which they should be rendered using
                //the glCullFace() and glFrontFace() functions, respectively.
                glCullFace(faceCulling.culledFace);//specifies which faces of a three-dimensional object should be culled
                glFrontFace(faceCulling.frontFace);//specifies the orientation of the front face of the object
            } else {
                glDisable(GL_CULL_FACE);
            }
            
            // Set the depth test based on the value of depthTest.enabled
            if (depthTesting.enabled) {
                glEnable(GL_DEPTH_TEST);//When depth testing is enabled, OpenGL determines which fragments of
                // a three-dimensional object should be drawn based on their distance from the viewer. This helps to ensure that objects appear
                // to be drawn in the correct order and that objects that are farther away from the viewer are obscured by objects that are closer.
                glDepthFunc(depthTesting.function);
                //to set the depth testing function for subsequent rendering operations.
                
              
            } else {
                glDisable(GL_DEPTH_TEST);
            }
            
            // Enable or disable blending based on the value of blend.enabled
            if (blending.enabled) {
                glEnable(GL_BLEND);
                //When blending is enabled,fragments that are drawn to the framebuffer
                //are combined with the existing color values in the framebuffer according to a blending equation.
                glBlendEquation(blending.equation);// the equation used is GL_FUNC_ADD means that the source and destination colors are added together.
                glBlendFunc(blending.sourceFactor, blending.destinationFactor);
                // sets the blending factors for source and destination colors.
                // The source color is the color of the pixel currently being drawn, (GL_SRC_ALPHA)the alpha value of the source color.
                // while the destination color is the color of the pixel already in the framebuffer.
                glBlendColor(blending.constantColor[0],blending.constantColor[1],blending.constantColor[2],blending.constantColor[3]);
                //sets a constant blend color to be used in blending operations.
                // It takes four parameters representing the red, green, blue, and alpha components of the color.
                
            } else {
                glDisable(GL_BLEND);
            }
            glDepthMask(depthMask);
              //hia hena m3molha set b true dayman i think
              // If depthMask is set to GL_TRUE, the depth buffer is writable and fragments that pass the depth test will update the depth buffer.
              // If depthMask is set to GL_FALSE, the depth buffer is read-only and fragments will not update the depth buffer.
            glColorMask(colorMask[0], colorMask[1], colorMask[2], colorMask[3]);
            ///specifies whether color components should be written to the color buffer during rendering.
            // It takes four boolean parameters that correspond to the red, green, blue, and alpha channels of the color buffer, respectively.
            //colorMask is a four-element boolean bvec4 (glm::bvec4 colorMask = {true, true, true, true}; )
            //if colorMask is set to [true, true, true, true], all color components will be written to the color buffer.
            // If colorMask is set to [true, false, true, false],
            // only the red and blue color components will be written to the color buffer,
            // while the green and alpha components will be masked out (not written to the buffer).
            //this can be useful in certain rendering scenarios where we want to selectively render certain color channels or control the blending of multiple render passes.
            }
            
          

        // Given a json object, this function deserializes a PipelineState structure
        void deserialize(const nlohmann::json& data);
    };

}