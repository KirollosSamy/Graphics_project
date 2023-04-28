#include "entity.hpp"
#include "../deserialize-utils.hpp"

#include <glm/gtx/euler_angles.hpp>

namespace our {

    // This function computes and returns a matrix that represents this transform
    // Remember that the order of transformations is: Scaling, Rotation then Translation
    // HINT: to convert euler angles to a rotation matrix, you can use glm::yawPitchRoll
    glm::mat4 Transform::toMat4() const {
        //TODO: (Req 3) Write this function

        // converting position, translation and rotation vectors each one to a 
        // 4x4 matrix (just as simple as it is)
         
        glm::mat4 Translation = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 Scaling = glm::scale(glm::mat4(1.0f), scale);
        glm::mat4 Rotation = glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);

        // Note : I guess they are multiplied in reverse order because the transormed vector is
        // multiplied to the right --> V'= T * R * S * V so we need to do scaling first then 
        // Rotation then translation 
        return   Translation * Rotation * Scaling; 
    }

     // Deserializes the entity data and components from a json object
    void Transform::deserialize(const nlohmann::json& data){
        position = data.value("position", position);
        rotation = glm::radians(data.value("rotation", glm::degrees(rotation)));
        scale    = data.value("scale", scale);
    }

}