#pragma once

#include "PickSystem.hpp"
#include "free-camera-controller.hpp"
#include "../ecs/entity.hpp"

#include <iostream>

namespace our
{
    // This should be called every frame to apply the game logic.
    void PickSystem::update(World *world)
    {

        while (!eventQueue.empty())
        {
            Event event = eventQueue.front();
            eventQueue.pop();
            std::cout << "inside while " << std::endl;
            switch (event)
            {
            case Event::KEY1_FOUND:
                std::cout << "inside while " << std::endl;
                if (app->getKeyboard().isPressed(GLFW_KEY_P)) // checking if P key is pressed
                {
                    std::cout << "key1 found" << std::endl; // adding this print to make sure code sequance runs correctly before debugging problems
                    Pick(world, "screw");
                }
                break;
            }
        }
    }
    void PickSystem::Pick(World *world, std::string object_name) // TODO: we can find a better way for searching an entity here
    {

        Entity *hand = world->GetEntity("hand");
        Entity *object = world->GetEntity(object_name);

        world->InsertChild("hand", "screw");

        glm::vec3 &position = object->localTransform.position;
        glm::vec3 &scale = object->localTransform.scale;
        position = glm::vec3(-1, -1.5, -1); // caught by hand
        // TODO: How can we reverse the direction of an object in the world space-->made by khaled & Nada
        // scale = glm::vec3(0.009/0.01 ,0.009/0.01, 0.09);
        scale = glm::vec3(0.009 / (hand->localTransform.scale.x / 10), 0.009 / (hand->localTransform.scale.y / 10), -0.09); // for screw
    }
}
