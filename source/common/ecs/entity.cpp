#include "entity.hpp"
#include "../deserialize-utils.hpp"
#include "../components/component-deserializer.hpp"

#include <glm/gtx/euler_angles.hpp>

namespace our {

    // This function returns the transformation matrix from the entity's local space to the world space
    // Remember that you can get the transformation matrix from this entity to its parent from "localTransform"
    // To get the local to world matrix, you need to combine this entities matrix with its parent's matrix and
    // its parent's parent's matrix and so on till you reach the root.
    glm::mat4 Entity::getLocalToWorldMatrix() const {
        //TODO: (Req 8) Write this function
        // 1. get the parrent of calling object
        // 2. get my localTransform 
        // 3. get parent localTransform
        // 3. multiply matricies untill there is no parent left
        // 4. return the result matrix

        Entity* Parent = this->parent;
        glm::mat4 translate_to_world = this->localTransform.toMat4();  // get the computed matrix for rotation, translation, scaling.

        while (Parent != nullptr)
        {
            translate_to_world = Parent->localTransform.toMat4() * translate_to_world;   // multiply the local transform of each parent each time and store in matrix
            Parent = Parent->parent;
        }
        
        return translate_to_world;
    }

    // Deserializes the entity data and components from a json object
    void Entity::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        name = data.value("name", name);
        localTransform.deserialize(data);
        if(data.contains("components")){
            if(const auto& components = data["components"]; components.is_array()){
                for(auto& component: components){
                    deserializeComponent(component, this);
                }
            }
        }
    }

}