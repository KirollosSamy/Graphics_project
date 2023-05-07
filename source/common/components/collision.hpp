#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our {

    // actually this component is useless but i added it to check if entity has collision component then i will apply collision system on it other than that 
    // collision is not needed at all 
    class CollisionComponent : public Component {
    public:
        bool collided = false;

        // The ID of this component type is "Collision"
        static std::string getID() { return "Collision"; }

        
        void deserialize(const nlohmann::json& data) override;
    };

}