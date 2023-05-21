#include "forward-renderer.hpp"
#include "../mesh/mesh-utils.hpp"
#include "../texture/texture-utils.hpp"
#include "../deserialize-utils.hpp"

namespace our {

    void ForwardRenderer::initialize(glm::ivec2 windowSize, const nlohmann::json& config, World* world) {
        // First, we store the window size for later use
        this->windowSize = windowSize;

        // Then we check if there is a sky texture in the configuration
        if (config.contains("sky")) {
            // First, we create a sphere which will be used to draw the sky
            this->skySphere = mesh_utils::sphere(glm::ivec2(16, 16));

            // We can draw the sky using the same shader used to draw textured objects
            ShaderProgram* skyShader = new ShaderProgram();
            skyShader->attach("assets/shaders/textured.vert", GL_VERTEX_SHADER);
            skyShader->attach("assets/shaders/textured.frag", GL_FRAGMENT_SHADER);
            skyShader->link();

            //TODO: (Req 10) Pick the correct pipeline state to draw the sky
            // Hints: the sky will be draw after the opaque objects so we would need depth testing but which depth funtion should we pick?
            // We will draw the sphere from the inside, so what options should we pick for the face culling.
            PipelineState skyPipelineState{};

            //To address the first hint, we need to determine which depth function to use. The depth function determines how the depth buffer will be updated during the rendering process. In this case, we want to draw the sky after the opaque objects, so we need to make sure that the depth of the sky fragments is greater than or equal to the depth of the opaque objects. Therefore, we should pick the GL_LEQUAL depth function.
            //To address the second hint, we need to determine which face culling options to use. We want to draw the sphere from the inside, which means that we need to make sure that the back faces of the sphere are rendered and the front faces are discarded. Therefore, we should enable face culling and set the culled face to GL_FRONT.
            //With these considerations in mind, we can set the pipeline state options for drawing the sky 
            //GL_LEQUAL is a depth function that specifies that fragments with a depth value less than or equal to the stored depth value pass the depth test. It is often used for rendering objects that are partially transparent and require correct depth sorting with the opaque objects behind them.

            skyPipelineState.faceCulling.enabled = true;
            skyPipelineState.faceCulling.culledFace = GL_FRONT;
            skyPipelineState.depthTesting.enabled = true;
            skyPipelineState.depthTesting.function = GL_LEQUAL;

            // Load the sky texture (note that we don't need mipmaps since we want to avoid any unnecessary blurring while rendering the sky)
            std::string skyTextureFile = config.value<std::string>("sky", "");
            Texture2D* skyTexture = texture_utils::loadImage(skyTextureFile, false);

            // Setup a sampler for the sky 
            Sampler* skySampler = new Sampler();
            skySampler->set(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            skySampler->set(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            skySampler->set(GL_TEXTURE_WRAP_S, GL_REPEAT);
            skySampler->set(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            // Combine all the aforementioned objects (except the mesh) into a material 
            this->skyMaterial = new TexturedMaterial();
            this->skyMaterial->shader = skyShader;
            this->skyMaterial->texture = skyTexture;
            this->skyMaterial->sampler = skySampler;
            this->skyMaterial->pipelineState = skyPipelineState;
            this->skyMaterial->tint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            this->skyMaterial->alphaThreshold = 1.0f;
            this->skyMaterial->transparent = false;
        }

        // Then we check if there is a postprocessing shader in the configuration
        if (config.contains("postprocess")) {
            //TODO: (Req 11) Create a framebuffer
            glGenFramebuffers(1, &postprocessFrameBuffer);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, postprocessFrameBuffer);

            //TODO: (Req 11) Create a color and a depth texture and attach them to the framebuffer
            // Hints: The color format can be (Red, Green, Blue and Alpha components with 8 bits for each channel).
            // The depth format can be (Depth component with 24 bits).
            colorTarget = texture_utils::empty(GL_RGBA8, windowSize);
            depthTarget = texture_utils::empty(GL_DEPTH_COMPONENT24, windowSize);

            glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTarget->getOpenGLName(), 0);
            glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTarget->getOpenGLName(), 0);

            //TODO: (Req 11) Unbind the framebuffer just to be safe
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

            // Create a vertex array to use for drawing the texture
            glGenVertexArrays(1, &postProcessVertexArray);

            // Create a sampler to use for sampling the scene texture in the post processing shader
            Sampler* postprocessSampler = new Sampler();
            postprocessSampler->set(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            postprocessSampler->set(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            postprocessSampler->set(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            postprocessSampler->set(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            // Create the post processing shader
            ShaderProgram* postprocessShader = new ShaderProgram();
            postprocessShader->attach("assets/shaders/fullscreen.vert", GL_VERTEX_SHADER);
            postprocessShader->attach(config.value<std::string>("postprocess", ""), GL_FRAGMENT_SHADER);
            postprocessShader->link();
            if(config.contains("addedTex")){
                addedTex = texture_utils::loadImage(config.value<std::string>("addedTex", ""));
            }
            
            effect_power = config.value("effect_power", effect_power);

            // Create a post processing material
            postprocessMaterial = new TexturedMaterial();
            postprocessMaterial->shader = postprocessShader;
            postprocessMaterial->texture = colorTarget;
            postprocessMaterial->sampler = postprocessSampler;
            // The default options are fine but we don't need to interact with the depth buffer
            // so it is more performant to disable the depth mask
            postprocessMaterial->pipelineState.depthMask = false;
        }

    }

    void ForwardRenderer::destroy() {
        // Delete all objects related to the sky
        if (skyMaterial) {
            delete skySphere;
            delete skyMaterial->shader;
            delete skyMaterial->texture;
            delete skyMaterial->sampler;
            delete skyMaterial;
        }
        // Delete all objects related to post processing
        if (postprocessMaterial) {
            glDeleteFramebuffers(1, &postprocessFrameBuffer);
            glDeleteVertexArrays(1, &postProcessVertexArray);
            delete colorTarget;
            delete depthTarget;
            delete postprocessMaterial->sampler;
            delete postprocessMaterial->shader;
            delete postprocessMaterial;
        }
    }

    void ForwardRenderer::render(World* world) {
        // First of all, we search for a camera and for all the mesh renderers
        CameraComponent* camera = nullptr;
        opaqueCommands.clear();
        transparentCommands.clear();
        for (auto entity : world->getEntities()) {
            // If we hadn't found a camera yet, we look for a camera in this entity
            if (!camera) camera = entity->getComponent<CameraComponent>();
            // If this entity has a mesh renderer component
            if (auto meshRenderer = entity->getComponent<MeshRendererComponent>(); meshRenderer) {
                // We construct a command from it
                RenderCommand command;
                command.localToWorld = meshRenderer->getOwner()->getLocalToWorldMatrix();
                command.center = glm::vec3(command.localToWorld * glm::vec4(0, 0, 0, 1));
                command.mesh = meshRenderer->mesh;
                command.material = meshRenderer->material;
                // if it is transparent, we add it to the transparent commands list
                if (command.material->transparent) {
                    transparentCommands.push_back(command);
                }
                else {
                    // Otherwise, we add it to the opaque command list
                    opaqueCommands.push_back(command);
                }
            }
        }

        // If there is no camera, we return (we cannot render without a camera)
        if (camera == nullptr) return;

        //TODO: (Req 9) Modify the following line such that "cameraForward" contains a vector pointing the camera forward direction
        // HINT: See how you wrote the CameraComponent::getViewMatrix, it should help you solve this one

        // The vector (0.0, 0.0, -1.0, 0.0) is a 4D homogeneous coordinate representing a vector pointing in the negative z-direction, with w=0 indicating that it is a vector, not a point.
        // The matrix M is a 4x4 transformation matrix that transforms coordinates from the local space of the camera to the world space of the scene. Multiplying the homogeneous vector (0.0, 0.0, -1.0, 0.0) by this matrix applies the transformation and returns a new 4D homogeneous vector representing the transformed vector.
        // After the multiplication, the resulting vector cameraForward contains the transformed vector in the world space. The x, y, and z components of the vector represent the new direction of the camera forward vector in the world space, while the w component is still 0.
        auto M = camera->getOwner()->getLocalToWorldMatrix();
        glm::vec3 cameraForward = M * glm::vec4(0.0, 0.0, -1.0, 0.0); // vector

        // This function is implementing a sorting algorithm for a vector of RenderCommand objects based on their distance to the camera. Specifically, it sorts the vector in descending order of distance, so that the commands that are farthest from the camera are drawn first.
        // The sorting function takes two RenderCommand objects as input, referred to as "first" and "second". It then calculates the distance of each object to the camera using the dot product of  the object's center position (as it is transformed already) in homogeneous coordinates with the camera forward vector.
        // Finally, the function returns a boolean value based on whether the distance of the first object is smaller than the distance of the second object. If it is, then the sorting function will consider the first object to be "less than" the second object, which means it will appear earlier in the sorted vector. If it is not, then the second object will appear earlier in the sorted vector.

        // The dot product between the camera forward vector and the vector from the camera to each object's center is used to calculate the distance between the camera and each object. This is because the camera forward vector represents the direction that the camera is facing.
        std::sort(transparentCommands.begin(), transparentCommands.end(), [cameraForward](const RenderCommand& first, const RenderCommand& second) {
            //TODO: (Req 9) Finish this function
            // HINT: the following return should return true "first" should be drawn before "second".
            float distanceToFirst = glm::dot(first.center, cameraForward);
            float distanceToSecond = glm::dot(second.center, cameraForward);
            return distanceToFirst < distanceToSecond;
            });

        //TODO: (Req 9) Get the camera ViewProjection matrix and store it in VP
        // from camera class

        // V represents the view matrix, which transforms positions from world space into camera space. It takes into account the position and orientation of the camera in the world.
        // P represents the projection matrix, which is responsible for the perspective projection of the scene. It transforms positions from camera space into canonical space.
        // The windowSize parameter is used to determine the aspect ratio of the projection. It represents the dimensions of the rendering viewport.
        // VP represents the combination of the view and projection matrices, which is used to transform positions from world space into canonical space. By multiplying a position in world space by this matrix, we obtain the position of the object in canonical space, which then used  to perform the actual rendering.

        glm::mat4 V = camera->getViewMatrix();
        glm::mat4 P = camera->getProjectionMatrix(this->windowSize);
        glm::mat4 VP = P * V;

        //TODO: (Req 9) Set the OpenGL viewport using viewportStart and viewportSize

       //The first argument is the x-coordinate of the lower left corner of the viewport rectangle.
       // The second argument is the y-coordinate of the lower left corner of the viewport rectangle.
       // The third argument is the width of the viewport rectangle.
       // The fourth argument is the height of the viewport rectangle.
       //glViewport is used to set the viewport to cover the entire window, from (0, 0) in the lower left corner to the x-coordinate this->windowSize.x and y-coordinate this->windowSize.y in the upper right corner. This means that any drawing that happens after this call will be limited to the area defined by the viewport.
        glViewport(0, 0, this->windowSize.x, this->windowSize.y);


        //TODO: (Req 9) Set the clear color to black and the clear depth to 1
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClearDepth(1.0f);


        //TODO: (Req 9) Set the color mask to true and the depth mask to true (to ensure the glClear will affect the framebuffer)

        // glColorMask controls which color channels (red, green, blue, and alpha) are enabled for writing. In this case, GL_TRUE is passed for each channel, which enables writing to all color channels. This means that any subsequent draw calls will be able to write to the color buffer.
        // glDepthMask controls whether or not writing to the depth buffer is enabled. In this case, GL_TRUE is passed, which enables writing to the depth buffer. This means that any subsequent draw calls will be able to write to the depth buffer, which is used for depth testing.

        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // enable writing to all color channels
        glDepthMask(GL_TRUE); // enable writing to depth buffer

        // If there is a postprocess material, bind the framebuffer
        if (postprocessMaterial) {
            //TODO: (Req 11) bind the framebuffer
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, postprocessFrameBuffer);
        }

        //TODO: (Req 9) Clear the color and depth buffers

       // This will clear both the color and depth buffers. The GL_COLOR_BUFFER_BIT flag specifies that the color buffer should be cleared,
       // and the GL_DEPTH_BUFFER_BIT flag specifies that the depth buffer should be cleared.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //the camera position is sent to the fragment shader to determine viewDir
        glm::vec3 cameraPos = M * glm::vec4(0.0, 0.0, 0.0, 1.0);

        //TODO: (Req 9) Draw all the opaque commands
        // Don't forget to set the "transform" uniform to be equal the model-view-projection matrix for each render command

      // The loop iterates through each opaque command and sets the model matrix of the mesh to its corresponding local-to-world matrix, which transforms the mesh from its local space to world space.
      // Next, the model-view-projection (MVP) matrix is calculated by multiplying the projection matrix (P) and the view matrix (V) with the model matrix. The MVP matrix transforms the vertices of the mesh from world space to canonical space, where they are transformed into pixels on the screen.
      // After the MVP matrix is calculated, the "transform" uniform variable in the shader program is set to the MVP matrix value. This variable is then used in the vertex shader to transform the vertices of the mesh.
      // Finally, the mesh is drawn using the material associated with the opaque command. The mesh is drawn using the draw() function, which typically contains the necessary OpenGL commands to send vertex and index data to the graphics pipeline for rendering.

        for (auto& cmd : opaqueCommands) {
            // Set the model matrix to localToWorld
            glm::mat4 modelMatrix = cmd.localToWorld;
            // Calculate the model-view-projection matrix
            glm::mat4 mvpMatrix = VP * modelMatrix;
            // Set the transform uniform to mvpMatrix
            cmd.material->setup();
            cmd.material->shader->set("transform", mvpMatrix);

            if (dynamic_cast<LitMaterial*>(cmd.material)) {
                glm::mat4 M_IT = glm::transpose(glm::inverse(modelMatrix));

                cmd.material->shader->set("M", modelMatrix);
                cmd.material->shader->set("M_IT", M_IT);
            }

            // Draw the mesh with the material
            cmd.mesh->draw();
        }
        // If there is a sky material, draw the sky
        if (this->skyMaterial) {

            //TODO: (Req 10) setup the sky material
            this->skyMaterial->setup();

            //TODO: (Req 10) Get the camera position
            //To get the camera position in world coordinates, we need to multiply the origin of the camera's local coordinate system (which is typically the position of the camera relative to its game object) by the game object's local-to-world transformation matrix. We can do this by creating a homogeneous vector with components (0, 0, 0, 1) (since we want to translate a point) and multiplying it by the transformation matrix.
            // calculates the camera position by creating a homogeneous vector with components (0, 0, 0, 1), multiplying it by the transformation matrix M, and discarding the fourth (w) component of the resulting vector to obtain a 3D position vector. The resulting vector gives the position of the camera in world coordinates.
            // glm::vec3 cameraPos = M * glm::vec4(0.0, 0.0, 0.0, 1.0); 

            //TODO: (Req 10) Create a model matrix for the sky such that it always follows the camera (sky sphere center = camera position)
            glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), cameraPos);

            //TODO: (Req 10) We want the sky to be drawn behind everything (in NDC space, z=1)
            //  We can acheive the is by multiplying by an extra matrix after the projection but what values should we put in it?
            // The first matrix sets the fourth row to be (0,0,1,1), which means that any point multiplied by this matrix will have a w value of 1. This would result in the point not being affected by the perspective division and therefore always remaining at z = 1 in normalized device coordinates (NDC).
            // For the purpose of rendering the sky sphere, it will position the sphere at the far plane of the camera frustum (z = 1) and ensure that it is always behind everything else.

            glm::mat4 alwaysBehindTransform = glm::mat4(
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 1.0f
            );

            //TODO: (Req 10) set the "transform" uniform
            glm::mat4 mvpMatrix = alwaysBehindTransform * VP * modelMatrix;
            this->skyMaterial->shader->set("transform", mvpMatrix);

            //TODO: (Req 10) draw the sky sphere
            this->skySphere->draw();
        }

        //TODO: (Req 9) Draw all the transparent commands
        // Don't forget to set the "transform" uniform to be equal the model-view-projection matrix for each render command
        // For each transparent command, the code sets the model matrix to the command's localToWorld matrix. Then, it calculates the model-view-projection matrix by multiplying the projection matrix (P) by the view matrix (V) and the model matrix.
        //After that, the code sets the "transform" uniform in the command's material shader to the calculated model-view-projection matrix. Finally, it draws the mesh using the command's material.

        for (auto& cmd : transparentCommands) {
            // Set the model matrix to localToWorld
            glm::mat4 modelMatrix = cmd.localToWorld;
            // Calculate the model-view-projection matrix
            glm::mat4 mvpMatrix = VP * modelMatrix;
            // Set the transform uniform to mvpMatrix
            cmd.material->setup();
            cmd.material->shader->set("transform", mvpMatrix);

            if (dynamic_cast<LitMaterial*>(cmd.material)) {
                glm::mat4 M_IT = glm::transpose(glm::inverse(modelMatrix));

                cmd.material->shader->set("M", modelMatrix);
                cmd.material->shader->set("M_IT", M_IT);
            }

            // Draw the mesh with the material
            cmd.mesh->draw();
        }


        // If there is a postprocess material, apply postprocessing
        if (postprocessMaterial) {
            //TODO: (Req 11) Return to the default framebuffer
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

            //TODO: (Req 11) Setup the postprocess material and draw the fullscreen triangle
            glBindVertexArray(postProcessVertexArray);
            postprocessMaterial->setup();

            if(addedTex  && applyEffect){
                glActiveTexture(GL_TEXTURE1);
                addedTex->bind();
                postprocessMaterial->sampler->bind(1);
                postprocessMaterial->shader->set("additional_sampler", 1);
                postprocessMaterial->shader->set("effect_power", effect_power);//TODO
            }
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
    }

}