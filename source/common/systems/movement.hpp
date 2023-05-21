#pragma once

#include "system.hpp"
#include "../ecs/world.hpp"
#include "../components/movement.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{

    // The movement system is responsible for moving every entity which contains a MovementComponent.
    // This system is added as a simple example for how use the ECS framework to implement logic.
    // For more information, see "common/components/movement.hpp"
    class MovementSystem : public System
    {
    public:
        float time1, time2, time3 = 0.0f;
        // This should be called every frame to update all entities containing a MovementComponent.
        void update(World *world, float deltaTime)
        {
            // For each entity in the world
            time1 += deltaTime;
            time2 += deltaTime;
            time3 += deltaTime;
            for (auto entity : world->getEntities())
            {
                // Get the movement component if it exists
                MovementComponent *movement = entity->getComponent<MovementComponent>();
                // If the movement component exists
                if (movement)
                {
                    // Change the position and rotation based on the linear & angular velocity and delta time.
                    if (entity->name == "spider")
                    {
                        glm::mat4 M = entity->localTransform.toMat4();
                        glm::vec3 front = glm::vec3(M * glm::vec4(0, 0, 1, 0));

                        entity->localTransform.position += deltaTime * movement->linearVelocity * front;

                        continue;
                    }
                    if (entity->name == "granny")
                    {
                        if (time1 < 100.0f)
                        {
                            time1 = 0;
                            const float a = 0.04f;
                            const float b = 4.11f;
                            const float c = -67.59f;
                            const float d = 1.00f;
                            // Define the initial point coordinates
                            float x0 = 1.0f;
                            float y0 = 2.0f;
                            float z0 = 3.0f;
                            // Define the step size for movement
                            const float step_size = 0.1f;
                            //-0.43x + 0.49y + -2.98z + 1.00 = 0
                            std::cout << "before plane1 " << std::endl;

                            // 0.04x + 4.11y + -67.59z + 1.00 = 0
                            glm::mat4 M = entity->localTransform.toMat4();
                            glm::vec3 front = glm::vec3(M * glm::vec4(0, 0, -1, 0));
                            entity->localTransform.position[0] += movement->linearVelocity[0] * (x0 + a * (d - a * x0 - b * y0 - c * z0) * step_size);
                            entity->localTransform.position[1] += movement->linearVelocity[1] * (y0 + b * (d - a * x0 - b * y0 - c * z0) * step_size);
                            entity->localTransform.position[2] += movement->linearVelocity[2] * (z0 + c * (d - a * x0 - b * y0 - c * z0) * step_size);

                            x0 = entity->localTransform.position[0];
                            y0 = entity->localTransform.position[1];
                            z0 = entity->localTransform.position[2];
                        }

                        if (time2 < 200 && time1 > 100)
                        {
                            time2 = 0;

                            const float a = 0.14f;
                            const float b = -0.96f;
                            const float c = -21.60f;
                            const float d = 1.00f;
                            // Define the initial point coordinates
                            float x0 = 1.0f;
                            float y0 = 2.0f;
                            float z0 = 3.0f;
                            // Define the step size for movement
                            const float step_size = 0.1f;

                            glm::mat4 M = entity->localTransform.toMat4();
                            glm::vec3 front = glm::vec3(M * glm::vec4(0, 0, -1, 0));
                            entity->localTransform.position[0] += movement->linearVelocity[0] * (x0 + a * (d - a * x0 - b * y0 - c * z0) * step_size);
                            entity->localTransform.position[1] += movement->linearVelocity[1] * (y0 + b * (d - a * x0 - b * y0 - c * z0) * step_size);
                            entity->localTransform.position[2] += movement->linearVelocity[2] * (z0 + c * (d - a * x0 - b * y0 - c * z0) * step_size);

                            x0 = entity->localTransform.position[0];
                            y0 = entity->localTransform.position[1];
                            z0 = entity->localTransform.position[2];
                        }
                        else if (time3 < 300 && time2 >200)
                        {
                            time3 = 0;
                            const float a = -0.55f;
                            const float b = -0.05f;
                            const float c = -0.01f;
                            const float d = 1.00f;
                            // Define the initial point coordinates
                            float x0 = 1.0f;
                            float y0 = 2.0f;
                            float z0 = 3.0f;
                            // Define the step size for movement
                            const float step_size = 0.1f;
                            glm::mat4 M = entity->localTransform.toMat4();
                            glm::vec3 front = glm::vec3(M * glm::vec4(0, 0, -1, 0));
                            entity->localTransform.position[0] += movement->linearVelocity[0] * (x0 + a * (d - a * x0 - b * y0 - c * z0) * step_size);
                            entity->localTransform.position[1] += movement->linearVelocity[1] * (y0 + b * (d - a * x0 - b * y0 - c * z0) * step_size);
                            entity->localTransform.position[2] += movement->linearVelocity[2] * (z0 + c * (d - a * x0 - b * y0 - c * z0) * step_size);

                            x0 = entity->localTransform.position[0];
                            y0 = entity->localTransform.position[1];
                            z0 = entity->localTransform.position[2];
                        }
                        continue;
                    }

                    if (entity->name == "boy")
                    {
                        glm::mat4 M = entity->localTransform.toMat4();
                        glm::vec3 front = glm::vec3(M * glm::vec4(0, 0, 1, 0));

                        entity->localTransform.position += deltaTime * movement->linearVelocity * front;

                        continue;
                    }

                    entity->localTransform.position += deltaTime * movement->linearVelocity; // position +=0.005 * (x,y,z)
                    entity->localTransform.rotation += deltaTime * movement->angularVelocity;
                }
            }
        }
    };

}
