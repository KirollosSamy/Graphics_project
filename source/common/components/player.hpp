#pragma once

#include "../ecs/component.hpp"

namespace our {

    struct GameState {
        int score = 0;
        bool keyFound = false;
        bool dead = false;
        float timeLeft;

        void deserialize(const nlohmann::json& gameStateData) {
            timeLeft = gameStateData.value("timeLeft", timeLeft);
        }
    };

    class PlayerSystem; // A forward declaration of the PlayerSystem Class

    // This component denotes that the current entity is a player
    // Only one instance of this class can be instantiated.
    class PlayerComponent : public Component {
        GameState gameState;
        friend PlayerSystem;
    public:
        static std::string getID() { return "Player"; }

        void deserialize(const nlohmann::json& data) override;
    };

}