#pragma once

#include "DropSystem.hpp"
#include "../ecs/entity.hpp"
#include "../components/player.hpp"
#include <iostream>

namespace our
{
    // This should be called every frame to apply the game logic.

    // TODO: Need to clear holded string in the player gamestate
    void DropSystem::Drop(World *world) // TODO: we can find a better way for searching an entity here
    {
        Entity *player = world->GetEntity("player");
        Entity *hand = world->GetEntity("hand");

        for (auto &Entity : world->getEntities())
        {
            if (Entity->parent)
            {
                if (Entity->parent->name == "hand" && app->getKeyboard().isPressed(GLFW_KEY_T))
                {
                    // we need to reset the string carrying the tool
                    PlayerComponent *playerComponent = player->getComponent<PlayerComponent>();
                    if (playerComponent)
                        playerComponent->gameState.holded = "";

                    glm::vec3 &position = Entity->localTransform.position;
                    Entity->parent = NULL;
                    glm::vec3 &rotation = Entity->localTransform.rotation;

                    // position = hand->localTransform.position + glm::vec3(47, 0, 25);
                    position = glm::vec3(54, 7.3, 23.0);
                    glm::vec3 &scale = Entity->localTransform.scale;
                    // position = glm::vec3(-1, -1.5, -1); // caught by hand
                    // TODO: How can we reverse the direction of an object in the world space-->made by khaled & Nada
                    // scale = glm::vec3(0.009/0.01 ,0.009/0.01, 0.09);

                    if (Entity->name == "screw")
                    {
                        position = glm::vec3(54, 7.3, 23.0);
                        scale = glm::vec3(0.0005 / (hand->localTransform.scale.x / 10), 0.0005 / (hand->localTransform.scale.y / 10), -0.05); // for screw
                    }
                    else if (Entity->name == "key1")
                    {
                        rotation.x += glm::radians(90.0f);
                        position = glm::vec3(45.7, 11.25, 15);
                        scale = glm::vec3(0.00045 / (hand->localTransform.scale.x / 10), 0.00045 / (hand->localTransform.scale.y / 10), -0.045); // for screw
                    }
                    else if (Entity->name == "key2")
                    {
                        rotation.x += glm::radians(90.0f);
                        position = glm::vec3(44.7, 10.1, 25.45);
                        scale = glm::vec3(0.0005 / (hand->localTransform.scale.x / 10), 0.0005 / (hand->localTransform.scale.y / 10), -0.05); // for screw
                    }
                    else if (Entity->name == "key3")
                    {
                        rotation.x += glm::radians(90.0f);
                        position = glm::vec3(57, 10.8, 19.63);
                        scale = glm::vec3(0.0005 / (hand->localTransform.scale.x / 10), 0.0005 / (hand->localTransform.scale.y / 10), -0.05); // for screw
                    }
                    else if (Entity->name == "key4")
                    {
                        rotation.x += glm::radians(90.0f);
                        position = glm::vec3(57.8, 7.16, 18.2);
                        scale = glm::vec3(0.0005 / (hand->localTransform.scale.x / 10), 0.0005 / (hand->localTransform.scale.y / 10), -0.05); // for screw
                    }
                    else if (Entity->name == "key5")
                    {
                        rotation.x += glm::radians(90.0f);
                        position = glm::vec3(47.7, 6.65, 21.45);
                        scale = glm::vec3(0.0005 / (hand->localTransform.scale.x / 10), 0.0005 / (hand->localTransform.scale.y / 10), -0.05); // for screw
                    }
                    else if (Entity->name == "key6")
                    {
                        rotation.x += glm::radians(90.0f);
                        position = glm::vec3(50.7, 3.85, 23.45);
                        scale = glm::vec3(0.0005 / (hand->localTransform.scale.x / 10), 0.0005 / (hand->localTransform.scale.y / 10), -0.05); // for screw
                    }
                    else if (Entity->name == "hummer")
                    {
                        position = glm::vec3(54.3, 11.2, 18.7);
                        scale = glm::vec3(0.000005 / (hand->localTransform.scale.x / 10), 0.000005 / (hand->localTransform.scale.y / 10), -0.0005); // for screw
                    }


                    notify(Event::MADE_NOISE);  // for granny system
                }
            }
        }
    };
}
