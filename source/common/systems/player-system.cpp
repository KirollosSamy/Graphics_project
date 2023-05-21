
#include "player-system.hpp"
#include "free-camera-controller.hpp"

namespace our
{

    // This function is called only once to search for the player entity
    // If a player found it returns true, otherwise false
    PlayerComponent* PlayerSystem::setPlayer(World* world) {
        for (Entity* entity : world->getEntities()) {
            player = entity->getComponent<PlayerComponent>();
            // a player must have a free camera component
            Component *freeCamera = entity->getComponent<FreeCameraControllerComponent>();

            if (player && freeCamera) return player;
            else return nullptr;
        }
        return nullptr;
    }

    // This should be called every frame to apply the game logic.
    GameStatus PlayerSystem::update(World *world)
    {

        GameStatus status = GameStatus::ONGOING;

        while (!eventQueue.empty())
        {
            Event event = eventQueue.front();

            eventQueue.pop();

            // Event e = static_cast<Event>();
            std::cout << " Event value " << static_cast<int>(event) << std::endl;

            switch (event)
            {
                std::cout << "reached here !";
            case Event::KEY_FOUND:
                // player->gameState.keyFound = true;
                status = GameStatus::WON;
                break;
            case Event::PLAYER_CAUGHT_BY_GRANNY:
                // player->gameState.dead = true;
                std::cout << "Player is dead" << std::endl;
                status = GameStatus::LOST;
                break;
            case Event::PLAYER_AT_DOOR:
                status = GameStatus::WON;
                break;
            case Event::FOUND_COIN:
                // player->gameState.score += 1;
                break;
            }
        }
        return status;
    }

}
