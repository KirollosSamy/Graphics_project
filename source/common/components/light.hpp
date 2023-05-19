#pragma once

#include "../ecs/component.hpp"
#include <glm/vec3.hpp>
#include "../shader/shader.hpp"

namespace our {

    // The base class for light components
    class Light : public Component {
    protected:
        glm::vec3 color;
        glm::vec3 position;

    public:
        static std::string getID() { return "Light"; }
        void deserialize(const nlohmann::json& data) override;

        virtual void send(ShaderProgram* shader) = 0;
    };

    class DirectionalLight : public Light {
        glm::vec3 direction;
        
        static int dirLightSize;

    public:
        static std::string getID() { return "Directional Light"; }
        void deserialize(const nlohmann::json& data) override;

        void send(ShaderProgram* shader) override;
        static void setSize(ShaderProgram* shader);
    };


    class PointLight : public Light {
        glm::vec3 attenuation;
        
        static int pointLightSize;

    public:
        static std::string getID() { return "Point Light"; }
        void deserialize(const nlohmann::json& data) override;

        void send(ShaderProgram* shader) override;
        static void setSize(ShaderProgram* shader);
    };

    class SpotLight : public Light {
        glm::vec3 direction;
        glm::vec3 attenuation;
        float innerCutoff;
        float outerCutoff;

        static int spotLightSize;

    public:
        static std::string getID() { return "Spot Light"; }
        void deserialize(const nlohmann::json& data) override;

        void send(ShaderProgram* shader) override;
        static void setSize(ShaderProgram* shader);

        void setDirection(glm::vec3 dir) {direction = dir;}
        void setPosition(glm::vec3 pos) {position = pos;}
    };
}