#pragma once

#include "DropSystem.hpp"
#include "../ecs/entity.hpp"

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
                    Entity->parent = NULL;

                    glm::vec3 &position = Entity->localTransform.position;

                    position = hand->localTransform.position + glm::vec3(47, 0, 25);
                    glm::vec3 &scale = Entity->localTransform.scale;
                    // position = glm::vec3(-1, -1.5, -1); // caught by hand
                    // TODO: How can we reverse the direction of an object in the world space-->made by khaled & Nada
                    // scale = glm::vec3(0.009/0.01 ,0.009/0.01, 0.09);
                    scale = glm::vec3(0.0009 / (hand->localTransform.scale.x / 10), 0.0009 / (hand->localTransform.scale.y / 10), -0.09); // for screw
                }
            }
        }
    };
}
