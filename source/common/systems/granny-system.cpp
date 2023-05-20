#pragma once
#include <iostream>
#include "granny-system.hpp"
#include "../components/movement.hpp"
#include "../ecs/entity.hpp"

namespace our
{

    void GrannySystem::moveGrannyRandomly(World *world, float deltaTime)
    {

        //    for (auto entity : world->getEntities())
        //      {

        // Get the movement component if it exists
        //   MovementComponent *movement = entity->getComponent<MovementComponent>();
        // If the movement component exists
        // if (movement)
        // Change the position and rotation based on the linear & angular velocity and delta time.
        // if (entity->name == "granny")
        // {
        // Create a vector of random numbers
        // std::vector<int> randomVector;
        // // Generate random numbers and store them in the vector
        // for (int i = 0; i < 3; ++i) {
        //     int random = std::rand() % 100;
        //     randomVector.push_back(random);
        // }
        // glm::mat4 M = entity->localTransform.toMat4();
        // glm::vec3 front = glm::vec3(M * glm::vec4(0, 0, -1, 0));
        // glm::vec3 randomFront = front * glm::vec3(randomVector[0], randomVector[1], randomVector[2]);
        // entity->localTransform.position += movement->linearVelocity * randomFront;
        //   std::cout << "inside random " << std::endl;
        //         Entity* granny=world->GetEntity("granny");
        //  std::cout << "inside random1" << std::endl;
        //         glm::vec3 &position = granny->localTransform.position;
        //         glm::vec3 &rotation = granny->localTransform.rotation;
        //         MovementComponent *movement = granny->getComponent<MovementComponent>();
        //          std::cout << "inside random2" << std::endl;
        //         glm::mat4 M = granny->localTransform.toMat4();
        //         glm::vec3 front = glm::vec3(M * glm::vec4(0, 0, -1, 0));
        //         std::cout << "inside random3" << std::endl;
        //         // undo last move
        //         //
        //         position += deltaTime * movement->linearVelocity * front;
        //         std::cout << "inside random4" << std::endl;
        //         rotation.y += glm::radians(90.0f) + glm::radians((std::rand() % 181) * 1.0f);
    }
    /*
    granny Checkes Player every frame,
    by Calculating the distance between granny Position vector and player Position vector
    if distance is less than 3, fire the PLAYER_CAUGHT_BY_GRANNY event and set gotCatched = true
    */
    void GrannySystem::grannyCheckesPlayer(World *world)
    {
        Entity *granny = world->GetEntity("granny");
        glm::vec3 &grannyPosition = granny->localTransform.position;

        Entity *player = world->GetEntity("player");
        glm::vec3 &playerPosition = player->localTransform.position;

        // Calculate the distance between the vectors
        float distance = glm::distance(grannyPosition, playerPosition);
        std::cout << "gotCatched  " << gotCatched << std::endl;

        // Check if the distance is less than 3
          std::cout << "distance  " << distance << std::endl;
        if (distance < 4.0f)
        {
            // fire the PLAYER_CAUGHT_BY_GRANNY event

            // gotCatched = true;
            // std::cout << "gotCatched  " << gotCatched << std::endl;
            notify(Event::PLAYER_CAUGHT_BY_GRANNY);
        }
    }
    /*
    on moving tools granny go to check this Positions sequentially
    */
    void GrannySystem::goPositions(World *world)
    {

        glm::vec3 position1 = {5, 97, 60};
        glm::vec3 position2 = {50, 45, 78};
        glm::vec3 position3 = {58, 22, 86};

        Entity *granny = world->GetEntity("granny");
        glm::vec3 &position = granny->localTransform.position;
        /*
        at first move granny 100 steps and check every itiration whether granny's position become = the position of the first tool
        if true, break from the loop and ask if gotCatched=0 which means granny does not catch the player yet.
        */
        for (int i = 0; i < 100; i++)
        {
            position += glm::vec3(1, 1, 1);
            if (position == position1)
                break;
        }

        if (!gotCatched)
        {
            for (int i = 0; i < 100; i++)
            {
                position += glm::vec3(1, 1, 1);
                if (position == position2)
                    break;
            }
        }

        if (!gotCatched)
        {
            for (int i = 0; i < 100; i++)
            {
                position += glm::vec3(1, 1, 1);
                if (position == position3)
                    break;
            }
        }
    }

    // This should be called every frame to apply the game logic.
    void GrannySystem::update(World *world, float deltaTime)
    {

        grannyCheckesPlayer(world);
        moveGrannyRandomly(world, deltaTime);

        //     while (!eventQueue.empty()) {
        //         Event event = eventQueue.front();
        //         eventQueue.pop();
        //         switch (event) {
        //         case Event::MADE_NOISE:
        //             goPositions(world);
        //             break;
        //         }
        //     }
        // }
    }
}
