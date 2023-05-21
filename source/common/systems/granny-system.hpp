#pragma once

#include "system.hpp"
#include "../ecs/world.hpp"

namespace our
{
       
    // The Granny system is responsible for handling game logic and the player state
    class GrannySystem : public System
    {
        // stores a pointer to the unique instance of the granny component.
    public:
        float time1 =0.0;
        float time2 = 0.0;
        float time3 = 0.0;
        float time4 = 0.0;
        float time5 = 0.0;
        float time6 = 0.0;
        float time7 = 0.0;
        float time8 = 0.0;
        float time9 = 0.0;
        float time10 = 0.0;
        float time11= 0.0;
        float time12 = 0.0;
        float time13 = 0.0;
        float time14 = 0.0;
        float time15 = 0.0;
        bool gotCatched{false}; // gotCatched is a boolean to indicate whether granny catched the player or not, intially false.

        // This should be called every frame to apply the game logic.
        void update(World *world, float deltaTime);

        // check the distance between the player and granny,
        void grannyCheckesPlayer(World *world);

        // make granny go to certain positions to check the player when there is noise
        void goPositions(World *world,float deltaTime);

        void moveGrannyRandomly(World *world, float deltaTime);
    };

}