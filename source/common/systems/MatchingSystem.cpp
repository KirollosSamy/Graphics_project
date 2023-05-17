#pragma once

#include "MatchingSystem.hpp"
#include "../ecs/entity.hpp"
#include "../components/player.hpp"

#include <iostream>

namespace our
{
    // this function matches components together to apply a certain logic.
    void MatchingSystem::Matching(World *world)
    {
        Entity *player = world->GetEntity("player");

        PlayerComponent *playerComponent = player->getComponent<PlayerComponent>();
        if (playerComponent)
            tool = playerComponent->gameState.holded;

        while (!eventQueue.empty())
        {
            Event event = eventQueue.front();
            eventQueue.pop();

            switch (event)
            {
            case Event::DOOR1_COLLISION:
                if (tool == "screw")
                {
                    // open door
                    //  1 - get entity with name door 1
                    //  2 - play with door transformations (position, rotation)
                    Entity *door1 = world->GetEntity("door1");
                    glm::vec3 &position = door1->localTransform.position;
                    glm::vec3 &rotation = door1->localTransform.rotation;
                    // (right left , up down , front back)
                    //    "position": [53.7, 11.4, 25.7],
                    position =  glm::vec3(52.8,11.4,26.5);
                    rotation.y = glm::radians(90.0f);
                }

                break;

                // door 3 open coordinates [52.9, 11.4, 20]  rotation 180

                // drawer open  [45.7, 11.2, 15]   [-180, -180, 180]
            }
        }
    };
}

/*
 match tool with [door , drawer]





*/