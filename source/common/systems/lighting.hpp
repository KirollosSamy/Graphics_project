#pragma once

#include "system.hpp"
#include "../components/light.hpp"
#include "../components/camera.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

#include <json/json.hpp>

namespace our
{

    class LightingSystem : public System {
        // stores a pointer to the unique instance of the player component.
        std::vector<Light*> lights;
        ShaderProgram* lightShader;
        SpotLight* flash;
        CameraComponent* camera;

        glm::vec3 ambient;

    public:
        // This function is called only once to search for light sources
        void initialize(World* world, const nlohmann::json& config);

        void update();

    };

}
