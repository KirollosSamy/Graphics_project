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
              case Event::DOOR2_COLLISION:
                if (tool == "key3")
                {
                    // open door
                    //  1 - get entity with name door 1
                    //  2 - play with door transformations (position, rotation)
                    Entity *door1 = world->GetEntity("door2");
                    glm::vec3 &position = door1->localTransform.position;
                    glm::vec3 &rotation = door1->localTransform.rotation;
                    // (right left , up down , front back)
                    //    "position": [46.85, 11.4, 20.5
                    position =  glm::vec3(45.85, 11.4, 21.2);
                    rotation.y = glm::radians(90.0f);
                    // rotation.z = glm::radians(90.0f);
                }
                break;
                 case Event::DOOR3_COLLISION:
                if (tool == "key2")
                {
                    // open door
                    //  1 - get entity with name door 1
                    //  2 - play with door transformations (position, rotation)
                    Entity *door1 = world->GetEntity("door3");
                    glm::vec3 &position = door1->localTransform.position;
                    glm::vec3 &rotation = door1->localTransform.rotation;
                    // (right left , up down , front back)
                    //    "position": [53.7, 11.4, 25.7],
                    position  =  glm::vec3(53, 11.4, 20);
                    // rotation.z = glm::radians(0.0f);  // the door is crazy about rotation 
                     rotation.y= glm::radians(180.0f); 
                }
                break;
                 case Event::DOOR5_COLLISION:
                if (tool == "key4")
                {
                    // open door
                    //  1 - get entity with name door 1
                    //  2 - play with door transformations (position, rotation)
                    Entity *door1 = world->GetEntity("door5");
                    glm::vec3 &position = door1->localTransform.position;
                    glm::vec3 &rotation = door1->localTransform.rotation;
                    // (right left , up down , front back)
                    //    "position": [53.7, 11.4, 25.7],
                    position =  glm::vec3(49.2, 7.8, 21);
                    rotation.y = glm::radians(90.0f);
                }
                break;
                 case Event::DOOR6_COLLISION:
                if (tool == "key1")
                {
                    // open door
                    //  1 - get entity with name door 1
                    //  2 - play with door transformations (position, rotation)
                    Entity *door1 = world->GetEntity("door6");
                    glm::vec3 &position = door1->localTransform.position;
                    glm::vec3 &rotation = door1->localTransform.rotation;
                    // (right left , up down , front back)
                    //    "position": [53.7, 11.4, 25.7],
                    position =  glm::vec3(53.5, 7.8, 24.2);
                    rotation.y= glm::radians(180.0f); 
                }
                break;
                 case Event:: PRISON_COLLISION:
                if (tool == "key5")
                {
                    // open door
                    //  1 - get entity with name door 1
                    //  2 - play with door transformations (position, rotation)
                    Entity *door1 = world->GetEntity("prison");
                    glm::vec3 &position = door1->localTransform.position;
                    glm::vec3 &rotation = door1->localTransform.rotation;
                    // (right left , up down , front back)
                    //    "position": [53.7, 11.4, 25.7],
                    position =  glm::vec3(52.8,11.4,26.5);
                    rotation.y = glm::radians(90.0f);

                    // TODO :
                    // make the boy go out 

                }
                break;

                 case Event:: DRAWER_COLLISION:
                if (tool == "hummer")
                {
                  
                    // open door
                    //  1 - get entity with name door 1
                    //  2 - play with door transformations (position, rotation)
                    Entity *door1 = world->GetEntity("drawer");
                    Entity *key1 = world->GetEntity("key1");
                    glm::vec3 &position = door1->localTransform.position;
                    glm::vec3 &rotation = door1->localTransform.rotation;

                    glm::vec3 &key_position = key1->localTransform.position;
                    
                    // (right left , up down , front back)
                    //    "position": [53.7, 11.4, 25.7],
                    key_position = glm::vec3(45.7, 11.25, 15);
                    position =  glm::vec3(45.7, 11.2, 15);
                    // rotation.y = glm::radians(90.0f);
                }
                break;


                // door 3 open coordinates [52.9, 11.4, 20]  rotation 180

                // drawer open  [45.7, 11.2, 15]   [-180, -180, 180]

                // door 6 open "position": [53.45, 7.8, 24.0], "rotation": [0, 180, 0],

                // key position if not child "position": [45.7, 11.25, 14.45],
        
            }
        }
    };
}