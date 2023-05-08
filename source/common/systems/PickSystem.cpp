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
                // if(app->getKeyboard().isPressed(GLFW_KEY_P)) // checking if P key is pressed
                std::cout << "key1 found" << std::endl; // adding this print to make sure code sequance runs correctly before debugging problems
                Pick(world, "screw");
                break;
            }
        }
    }
    void PickSystem::Pick(World *world, std::string object_name) // TODO: we can find a better way for searching an entity here
    {
        // first step change the object to player's children
        // second change the object's position to player's hand--->const position
        //  Entity *player = world->GetEntity("player");
        Entity *object = world->GetEntity(object_name);


        // std::cout << player->name << std::endl << object->name << std::endl;

        world->InsertChild();

        // TODO: we need to change the position of the object to player's hand

        glm::vec3 &position = object->localTransform.position;
        position += glm::vec3(5, 5, 5);

        // i need to remove my hand
    }
}
