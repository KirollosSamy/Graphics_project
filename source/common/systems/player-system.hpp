#pragma once

#include "system.hpp"
#include "../components/player.hpp"
#include "../ecs/world.hpp"

namespace our
{
    enum class GameStatus {
        WON,
        LOST,
        ONGOING
    };

    // The Player system is responsible for handling game logic and the player state
    class PlayerSystem : public System {
    // stores a pointer to the unique instance of the player component.
    PlayerComponent* player;
    public:
        // This function is called only once to search for the player entity
        // If a player found it returns true, otherwise false
        bool setPlayer(World* world);

        // This should be called every frame to apply the game logic. 
        GameStatus update(World* world);

    };

}
