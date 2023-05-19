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
            if (app->getKeyboard().isPressed(GLFW_KEY_P)) // checking if P key is pressed
                switch (event)
                {
                case Event::KEY1_FOUND:
                    Pick(world, "key1");
                    break;
                case Event::KEY2_FOUND:
                    Pick(world, "key2");
                    break;
                case Event::KEY3_FOUND:
                    Pick(world, "key3");
                    break;
                case Event::KEY4_FOUND:
                    Pick(world, "key4");
                    break;
                case Event::KEY5_FOUND:
                    Pick(world, "key5");
                    break;
                case Event::HUMMER_FOUND:
                    Pick(world, "hummer");
                    break;

                case Event::SCREW_FOUND:
                    Pick(world, "screw");
                    break;
                }
        }
    }
    void PickSystem::Pick(World *world, std::string object_name) // TODO: we can find a better way for searching an entity here
    {

        Entity *hand = world->GetEntity("hand");
        Entity *object = world->GetEntity(object_name);

        // insert child to hand
        world->InsertChild("hand", object_name);

        glm::vec3 &position = object->localTransform.position;
        glm::vec3 &scale = object->localTransform.scale;
        glm::vec3 &rotation = object->localTransform.rotation;

        position = glm::vec3(-1, -1.5, -1); // caught by hand

        if (object_name == "screw")
        {
            scale = glm::vec3(0.009 / (hand->localTransform.scale.x / 10), 0.009 / (hand->localTransform.scale.y / 10), -0.09);
        }
        else if (object_name == "hummer")
        {
            scale = glm::vec3(0.0001 / (hand->localTransform.scale.x / 10), 0.0001 / (hand->localTransform.scale.y / 10), -0.001); // for hummer
        }
        else // keys
        { 
            rotation.x -= glm::radians(90.0f);
            scale = glm::vec3(-0.005 / (hand->localTransform.scale.x / 10), 0.005 / (hand->localTransform.scale.y / 10), -0.05);
        }
    }
}
