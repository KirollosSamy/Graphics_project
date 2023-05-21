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
        float timer = 0.0;
        // This should be called every frame to update all entities containing a MovementComponent.
        void update(World *world, float deltaTime)
        {
            // For each entity in the world
            timer += deltaTime;

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
                        // 5.7->floor one
                        // 2.7->el2arde
                        // 9.4 eli fo2
                        if (timer < 20.0)
                        {
                            std::cout << "eldor 33333 eltalet aho " << std::endl;
                            glm::mat4 M = entity->localTransform.toMat4();
                            glm::vec3 front = glm::vec3(M * glm::vec4(0, 0, -1, 0));
                            entity->localTransform.position[0] += deltaTime * movement->linearVelocity[0] * front[0];
                            entity->localTransform.position[1] = 9.4;
                            entity->localTransform.position[2] += deltaTime * movement->linearVelocity[2] * front[2];
                            continue;
                        }
                        else if (timer < 2 * 20.0)
                        {
                            std::cout << "eldor 222222 eltane aho " << std::endl;
                            glm::mat4 M = entity->localTransform.toMat4();
                            glm::vec3 front = glm::vec3(M * glm::vec4(0, 0, -1, 0));
                            entity->localTransform.position[0] += deltaTime * movement->linearVelocity[0] * front[0];
                            entity->localTransform.position[1] = 5.7;
                            entity->localTransform.position[2] += deltaTime * movement->linearVelocity[2] * front[2];
                            continue;
                        }
                        else if (timer < 3 * 20.0)
                        {
                            std::cout << "eldor 11111111 elawel aho " << std::endl;
                            glm::mat4 M = entity->localTransform.toMat4();
                            glm::vec3 front = glm::vec3(M * glm::vec4(0, 0, -1, 0));
                            entity->localTransform.position[0] += deltaTime * movement->linearVelocity[0] * front[0];
                            entity->localTransform.position[1] = 2.7;
                            entity->localTransform.position[2] += deltaTime * movement->linearVelocity[2] * front[2];
                            continue;
                        }

                        // Reset timer after the third condition
                        if (timer >= 3 * 20.0)
                        {
                            timer = 0.0;
                        }
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
};

