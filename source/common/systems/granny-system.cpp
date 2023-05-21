#pragma once
#include <iostream>
#include "granny-system.hpp"
#include "../components/movement.hpp"
#include "../ecs/entity.hpp"

namespace our
{
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
        if (distance < 3.0f)
        {
            // fire the PLAYER_CAUGHT_BY_GRANNY event
            // std::cout << "gotCatched  " << gotCatched << std::endl;
            notify(Event::PLAYER_CAUGHT_BY_GRANNY);
            gotCatched = true;
        }
    }
    /*
    on moving tools granny go to check this Positions sequentially
    */
void GrannySystem::goPositions(World* world,float deltaTime) {
        timer += deltaTime;
        
        glm::vec3 p7=glm::vec3(0.0f, 0.0f, 0.0f);glm::vec3 p5=glm::vec3(48.45f, 7.8f, 20.2f);
        glm::vec3 p6=glm::vec3(53.0f, 7.8f, 23.3f);glm::vec3 p10=glm::vec3(57.8f, 7.16f, 18.2f);
        glm::vec3 p11=glm::vec3(47.7f, 6.65f, 21.45f);glm::vec3 p14=glm::vec3(54.0f, 7.3f, 23.0f);
        glm::vec3 p12=glm::vec3(50.8f, 4.7f, 28.4f);glm::vec3 p15=glm::vec3(45.7f, 11.25f, 14.45f);
        glm::vec3 p1=glm::vec3(3.7f, 11.4f, 25.7f);glm::vec3 p2=glm::vec3(46.85f, 11.4f, 20.2f);
        glm::vec3 p3=glm::vec3(52.0f, 11.4f, 19.1f);glm::vec3 p4=glm::vec3(57.6f, 11.4f, 14.8f);
        glm::vec3 p13=glm::vec3(54.8f, 11.2f, 18.7f);glm::vec3 p8=glm::vec3(44.7f, 10.1f, 25.45f);
        glm::vec3 p9=glm::vec3(57.0f, 10.8f, 19.63f);
        
        Entity *granny = world->GetEntity("granny"); glm::vec3 &position = granny->localTransform.position;
        /*
        at first move granny 100 steps and check every itiration whether granny's position become = the position of the first tool
        if true, break from the loop and ask if gotCatched=0 which means granny does not catch the player yet.
        */
   if (timer < conditionDuration ) {position=p1;}
   else if (timer < 2 * conditionDuration && gotCatched!=1) {position=p2;}
   else if (timer < 3 * conditionDuration && gotCatched!=1) {position=p3;}
   else if (timer < 4 * conditionDuration && gotCatched!=1) {position=p4;}
   else if (timer < 5 * conditionDuration && gotCatched!=1) {position=p5;}
   else if (timer < 6 * conditionDuration && gotCatched!=1) {position=p6;}
   else if (timer < 7 * conditionDuration && gotCatched!=1) {position=p7;}
   else if (timer < 8 * conditionDuration && gotCatched!=1) {position=p8;}
   else if (timer < 9 * conditionDuration && gotCatched!=1) {position=p9;}
   else if (timer < 10 * conditionDuration && gotCatched!=1) {position=p10;}
   else if (timer < 11 * conditionDuration && gotCatched!=1) {position=p11;}
   else if (timer < 12 * conditionDuration && gotCatched!=1) {position=p12;}
   else if (timer < 13 * conditionDuration && gotCatched!=1) {position=p13;}
   else if (timer < 14 * conditionDuration && gotCatched!=1) {position=p14;}
   else if (timer < 15 * conditionDuration && gotCatched!=1) {position=p15;}
   // Reset timer after the third condition
   if (timer >= 15 * conditionDuration) {timer = 0.0;}
}

    // This should be called every frame to apply the game logic. 
    void GrannySystem::update(World* world,float deltaTime) {
       grannyCheckesPlayer(world);
        while (!eventQueue.empty()) {
            Event event = eventQueue.front();
            eventQueue.pop();
            switch (event) {
            case Event::MADE_NOISE:
                goPositions(world,deltaTime);
                break;
            }
        }
    }
}