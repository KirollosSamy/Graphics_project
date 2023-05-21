
#include "lighting.hpp"
#include "../ecs/world.hpp"
#include "../asset-loader.hpp"

#include <glm/glm.hpp>

namespace our
{
    // This function is called only once to search for light sources
    void LightingSystem::initialize(World* world, const nlohmann::json& config) {
        // set the ambient value for the entire scene
        ambient = config.value("ambient", glm::vec3(0.05f, 0.05f, 0.05f));

        //get the light shader to use it to send global uniforms
        lightShader = AssetLoader<ShaderProgram>::get("light");

        // Find all ligh sources once for efficiency
        for (Entity* entity : world->getEntities()) {
            // If this entity has a light component then it's a light source
            if (Light* light = entity->getComponent<Light>(); light) {
                lights.push_back(light);
                if (entity->name == "flash") flash = (SpotLight*)light;
            }

            // get camera component so that flashLight will follow it
            if (!camera) camera = entity->getComponent<CameraComponent>();
        }
    }

    void LightingSystem::update() {

        glm::mat4 M = camera->getOwner()->getLocalToWorldMatrix();
        glm::vec3 cameraForward = M * glm::vec4(0.0, 0.0, -1.0, 0.0);
        glm::vec3 cameraPos = M * glm::vec4(0.0, 0.0, 0.0, 1.0);


        // The position & direction of the flash light should follow the camera
        if (flash) {
            flash->setDirection(cameraForward);
            flash->setPosition(cameraPos);
        }

        // send global uniforms to light shader, that is uniforms that don't change with each mesh
        lightShader->use();

        lightShader->set("cameraPos", cameraPos);
        lightShader->set("ambientLight", ambient);

        for (Light* light : lights)
            light->send(lightShader);

        // send the size for each type of light sources to the light shader
        DirectionalLight::setSize(lightShader);
        PointLight::setSize(lightShader);
        SpotLight::setSize(lightShader);
    }
}
