#include "light.hpp"
#include "../deserialize-utils.hpp"
#include "../ecs/entity.hpp"

#include <json/json.hpp>

namespace our {
    // Initialize number of light sources for each type (static members)
    int DirectionalLight::dirLightSize = 0;
    int PointLight::pointLightSize = 0;
    int SpotLight::spotLightSize = 0;

    void Light::deserialize(const nlohmann::json& data) {
        if (!data.is_object()) return;

        color = data.value("color", color);

        // Set the position using the model matrix of the owner entity
        position = getOwner()->getLocalToWorldMatrix() * glm::vec4(0.0, 0.0, 0.0, 1);
    }



    void DirectionalLight::deserialize(const nlohmann::json& data) {
        Light::deserialize(data);

        if (!data.is_object()) return;
        direction = glm::normalize(data.value("direction", direction));
    }

    void DirectionalLight::setSize(ShaderProgram* shader) {
        shader->set("dirLightSize", dirLightSize);

        //reset number of light sources
        dirLightSize = 0;
    }

    void DirectionalLight::send(ShaderProgram* shader) {
        //dirLightSize is incremented with each call so that at the end it holds the total size
        std::string uniformPath = "dirLights[" + std::to_string(dirLightSize++) + "].";

        shader->set((uniformPath + "color").c_str(), color);
        shader->set((uniformPath + "position").c_str(), position);

        shader->set((uniformPath + "direction").c_str(), direction);
    }



    void PointLight::deserialize(const nlohmann::json& data) {
        Light::deserialize(data);

        if (!data.is_object()) return;
        attenuation = data.value("attenuation", attenuation);
    }

    void PointLight::send(ShaderProgram* shader) {
        //dirLightSize is incremented with each call so that at the end it holds the total size
        std::string uniformPath = "pointLights[" + std::to_string(pointLightSize++) + "].";

        shader->set((uniformPath + "color").c_str(), color);
        shader->set((uniformPath + "position").c_str(), position);

        shader->set((uniformPath + "attenuation").c_str(), attenuation);
    }

    void PointLight::setSize(ShaderProgram* shader) {
        shader->set("pointLightSize", pointLightSize);

        //reset number of light sources
        pointLightSize = 0;
    }



    void SpotLight::deserialize(const nlohmann::json& data) {
        Light::deserialize(data);

        if (!data.is_object()) return;
        direction = glm::normalize(data.value("direction", direction));
        attenuation = data.value("attenuation", attenuation);
        innerCutoff = data.value("innerCutoff", innerCutoff);
        outerCutoff = data.value("outerCutoff", outerCutoff);
    }

    void SpotLight::send(ShaderProgram* shader) {
        //dirLightSize is incremented with each call so that at the end it holds the total size
        std::string uniformPath = "spotLights[" + std::to_string(spotLightSize++) + "].";

        shader->set((uniformPath + "color").c_str(), color);
        shader->set((uniformPath + "position").c_str(), position);

        shader->set((uniformPath + "attenuation").c_str(), attenuation);
        shader->set((uniformPath + "direction").c_str(), direction);

        shader->set((uniformPath + "innerCutoff").c_str(), innerCutoff);
        shader->set((uniformPath + "outerCutoff").c_str(), outerCutoff);
    }

    void SpotLight::setSize(ShaderProgram* shader) {
        shader->set("spotLightSize", spotLightSize);

        //reset number of light sources
        spotLightSize = 0;
    }
}