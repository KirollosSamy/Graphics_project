#pragma once

#include "system.hpp"
#include "../ecs/world.hpp"
#include "../components/collision.hpp"
#include "../components/mesh-renderer.hpp"
#include "../components/movement.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

#include "events.hpp"

#include <iostream>

namespace our
{

    /*
        Collision System :
        -----------------------------------------------------------------

            is a simple collision system that is responsible for detecting collisions between entities.
            once the entity has collision component in it then this system can work out to detect collisions.

        Note :
        -----------------------------------------------------------------

            the collision as a concept is very hard and complex to implement if i want to check with the
            actual mesh shape because some shapes may have very complex structures which will make it very hard and inefficient
            to work with insteda we can approximate this shape to simple shapes like a sphere, cube, cylinder, rectangle, etc.
            this way will make our algorithm simple and efficient.


        --> object -> key -> communicate (system -> HandOfplayer) -> player --> children (Key)

    */
    class CollisionSystem : public System
    {
    public:
        std::pair<glm::vec3, glm::vec3> getCollisionBox(Entity *entity)
        {
            // get local to world matrix
            glm::mat4 M = entity->getLocalToWorldMatrix();

            // get the mesh component to get its min and max positions
            MeshRendererComponent *meshComponent = entity->getComponent<MeshRendererComponent>();

            // std::cout <<"inside getCollisionBox "<< entity->name << std::endl;

            if (!meshComponent)
                std::cout << "No mesh component " << std::endl;

            // min and max positions of box
            glm::vec3 minPos = meshComponent->mesh->min;
            glm::vec3 maxPos = meshComponent->mesh->max;

            /*
                construct the box :
                    - we need 8 verticies for making the box in 3d space.
                      imagine with me how can i get the 8 verticies of the box from
                      only knowing the min vertix and max vertix. 🤔

                    -> too simple try it on paper.


                                       +------+  <- (x',y',z') (length,width,height)
                                     /       /|
                                    /       / |
                                    +------+  |
                                    |      |  |
                                    |      |  + <- (length,width,z)
                                    |      | /
                                    |      |/
                    (x,y,z) ->      +------+

            */

            glm::vec3 boxes[8] = {
                glm::vec3(minPos.x, minPos.y, minPos.z),
                glm::vec3(minPos.x, maxPos.y, minPos.z),
                glm::vec3(maxPos.x, maxPos.y, minPos.z),
                glm::vec3(maxPos.x, minPos.y, minPos.z),
                glm::vec3(minPos.x, minPos.y, maxPos.z),
                glm::vec3(minPos.x, maxPos.y, maxPos.z),
                glm::vec3(maxPos.x, maxPos.y, maxPos.z),
                glm::vec3(maxPos.x, minPos.y, maxPos.z)};

            // transform each point to its position in space

            for (int i = 0; i < 8; i++)
            {
                boxes[i] = M * glm::vec4(boxes[i], 1.0);
            }

            glm::vec3 minPos_afterTransformation = glm::vec3(std::numeric_limits<float>::max());
            glm::vec3 maxPos_afterTransformation = glm::vec3(std::numeric_limits<float>::min());

            // loop over each vertex
            for (auto &vertix : boxes)
            {
                minPos_afterTransformation.x = std::min(minPos_afterTransformation.x, vertix.x);
                minPos_afterTransformation.y = std::min(minPos_afterTransformation.y, vertix.y);
                minPos_afterTransformation.z = std::min(minPos_afterTransformation.z, vertix.z);
                maxPos_afterTransformation.x = std::max(maxPos_afterTransformation.x, vertix.x);
                maxPos_afterTransformation.y = std::max(maxPos_afterTransformation.y, vertix.y);
                maxPos_afterTransformation.z = std::max(maxPos_afterTransformation.z, vertix.z);
            }

            // std::cout <<entity->name<< "    minPos_afterTransformation " << minPos_afterTransformation.x << " " << minPos_afterTransformation.y << " " << minPos_afterTransformation.z << std::endl;
            // std::cout <<entity->name<< "    maxPos_afterTransformation " << maxPos_afterTransformation.x << " " << maxPos_afterTransformation.y << " " << maxPos_afterTransformation.z << std::endl;

            return std::make_pair(minPos_afterTransformation, maxPos_afterTransformation);
        }

        bool check_collision(const glm::vec3 &box1_min, const glm::vec3 &box1_max,
                             const glm::vec3 &box2_min, const glm::vec3 &box2_max)
        {
            // Check along x-axis
            if (box1_max.x < box2_min.x || box2_max.x < box1_min.x)
            {
                return false;
            }

            // Check along y-axis
            if (box1_max.y < box2_min.y || box2_max.y < box1_min.y)
            {
                return false;
            }

            // Check along z-axis
            if (box1_max.z < box2_min.z || box2_max.z < box1_min.z)
            {
                return false;
            }

            // The two boxes are colliding
            return true;
        }

        void update(World *world, float deltaTime)
        {
            // For each entity in the world
            for (auto &entity : world->getEntities()) // [e1 e2 e3]
            {
                // Get the position of the entity
                glm::vec3 &position = entity->localTransform.position;

                // Get ortientation of the entity
                glm::vec3 &rotation = entity->localTransform.rotation;

                // Get the collision component if it exists
                CollisionComponent *collision = entity->getComponent<CollisionComponent>();
                // If it exists check if it is colliding with another entity.
                if (collision)
                {
                    auto boxPositions = getCollisionBox(entity);
                    // std::cout << "COLLISION" << std::endl;

                    // done with this entity now loop on other entities
                    for (auto &otherEntity : world->getEntities())
                    {

                        // if the other entity is not me (assuming name is unique)
                        // player has no mesh so i spent almost 2 hours debuging to catch that so when it comes to player i need to skip it for now
                        // (i will think of a way to implement collision of it later)
                        // TODO : ignore collision with child of hand
                        if (otherEntity->parent)
                        {
                            if (otherEntity->parent->name == "hand")
                                continue;
                        }

                        if (entity->name == otherEntity->name || otherEntity->name == "player" || otherEntity->name == "house") // skip me -> Note: this condition can be modified to ignore things also from collision system if needed
                            continue;

                        // general collision concept
                        auto otherBoxPositions = getCollisionBox(otherEntity);

                        if (check_collision(boxPositions.first, boxPositions.second, otherBoxPositions.first, otherBoxPositions.second))
                        {
                            MovementComponent *movement = entity->getComponent<MovementComponent>();
                            std::cout << "COLLISION  " << deltaTime<< std::endl;
                            std::cout << "entity " << entity->name <<" otherEntity "<<otherEntity->name <<std::endl;

                            // firing event to notify key1 is found  (testing)
                            // notify(Event::KEY1_FOUND);

                            if (movement) // if it exists
                            {
                                // working on monkey special case
                                // glm::vec3 up = glm::vec3(entity->localTransform.toMat4() * glm::vec4(0, 1, 0, 0));

                                // undoing last movement
                                position -= movement->linearVelocity * deltaTime;
                            }
                        }
                    }
                }
            }
        }
    };

}
