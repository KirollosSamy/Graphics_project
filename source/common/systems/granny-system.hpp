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
        bool gotCatched{false}; // gotCatched is a boolean to indicate whether granny catched the player or not, intially false.

        // This should be called every frame to apply the game logic.
        void update(World *world, float deltaTime);

        // check the distance between the player and granny,
        void grannyCheckesPlayer(World *world);

        // make granny go to certain positions to check the player when there is noise
        void goPositions(World *world);

        void moveGrannyRandomly(World *world, float deltaTime);
    };

}