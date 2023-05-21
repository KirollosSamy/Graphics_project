#pragma once

#include "system.hpp"
#include "../ecs/world.hpp"
#include "../ecs/entity.hpp"
#include "../components/collision.hpp"
#include "../components/mesh-renderer.hpp"
#include "../components/movement.hpp"
#include "../components/player.hpp"
#include "../components/free-camera-controller.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

#include "forward-renderer.hpp"

#include "../application.hpp"

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
        Application *app;
        float time = 0.0;
        float time1 = 0.0;
        float time2 = 0.0;
        float time3 = 0.0;
        bool postprocessEffect = false;
        int lives = 10;

        void setApp(Application *app)
        {
            this->app = app;
        }

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

        /// @brief 
        /// @param world 
        /// @param deltaTime 
        /// @param renderer 
        /// @return 
        std::pair<std::string, int> update(World *world, float deltaTime, ForwardRenderer *renderer)
        {
            time += deltaTime;
            time1 += deltaTime;
            time2 += deltaTime;
            time3 += deltaTime;
            // For each entity in the world
            std::string text = "You thought you were alone... You were wrong.";

            if (time > 10.0f && postprocessEffect)
            {
                time = 0;
                postprocessEffect = false;
                renderer->changeApply(false);
                // notify(Event::NORMAL_MUSIC);
            }

            if (time > 500)
            {
                time = 0;
                notify(Event::NORMAL_MUSIC);
            }

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
                            {
                                // here we are setting the object name the player hold so to use it in matching system
                                Entity *player = world->GetEntity("player");

                            
                                PlayerComponent *playerComponent = player->getComponent<PlayerComponent>();
                                if (playerComponent)
                                {
                                    playerComponent->gameState.holded = otherEntity->name;
                                }
                                else
                                    std::cout << " no player component found" << std::endl;
                            }

                            continue;
                        }

                        if (entity->name == otherEntity->name || otherEntity->name == "player" || otherEntity->name == "house" || otherEntity->name == "collided") // skip me -> Note: this condition can be modified to ignore things also from collision system if needed
                            continue;

                        // general collision concept
                        auto otherBoxPositions = getCollisionBox(otherEntity);

                        if (check_collision(boxPositions.first, boxPositions.second, otherBoxPositions.first, otherBoxPositions.second))
                        {
                            MovementComponent *movement = entity->getComponent<MovementComponent>();
                            std::cout << "COLLISION  " << deltaTime << std::endl;
                            std::cout << "entity " << entity->name << " otherEntity " << otherEntity->name << std::endl;
                            if (entity->name == "hand")
                                if ((otherEntity->name == "door1" || otherEntity->name == "wall") || otherEntity->name == "door2" || otherEntity->name == "door3" || otherEntity->name == "door4" || otherEntity->name == "door5" || otherEntity->name == "door6" || otherEntity->name == "prison" || otherEntity->name == "prison1")
                                {
                                    if (otherEntity->name == "door1")
                                    {
                                        notify(Event::DOOR1_COLLISION);
                                    }
                                    else if (otherEntity->name == "door2")
                                    {
                                        notify(Event::DOOR2_COLLISION);
                                    }
                                    else if (otherEntity->name == "door3")
                                    {
                                        notify(Event::DOOR3_COLLISION);
                                    }
                                    else if (otherEntity->name == "door4")
                                    {
                                        notify(Event::DOOR4_COLLISION);
                                    }
                                    else if (otherEntity->name == "door5")
                                    {
                                        notify(Event::DOOR5_COLLISION);
                                    }
                                    else if (otherEntity->name == "door6")
                                    {
                                        notify(Event::DOOR6_COLLISION);
                                    }
                                    else if (otherEntity->name == "prison")
                                    {
                                        notify(Event::PRISON_COLLISION);
                                    }
                                    Entity *player = world->GetEntity("player");

                                    FreeCameraControllerComponent *controller = player->getComponent<FreeCameraControllerComponent>();

                                    glm::vec3 current_sensitivity = controller->positionSensitivity;

                                    glm::mat4 M = player->localTransform.toMat4();
                                    glm::vec3 front = glm::vec3(M * glm::vec4(0, 0, -1, 0)),
                                              up = glm::vec3(M * glm::vec4(0, 1, 0, 0)),
                                              right = glm::vec3(M * glm::vec4(1, 0, 0, 0));

                                    glm::vec3 &position_player = player->localTransform.position;

                                    if (app->getKeyboard().isPressed(GLFW_KEY_W))
                                        position_player -= front * (deltaTime * current_sensitivity.z);

                                    if (app->getKeyboard().isPressed(GLFW_KEY_S))
                                        position_player += front * (deltaTime * current_sensitivity.z);

                                    if (app->getKeyboard().isPressed(GLFW_KEY_A))
                                        position_player += right * (deltaTime * current_sensitivity.x);

                                    if (app->getKeyboard().isPressed(GLFW_KEY_D))
                                        position_player -= right * (deltaTime * current_sensitivity.x);
                                }

                            if (entity->name == "boy")
                            {
                                if (otherEntity->name == "prison" || otherEntity->name == "prison1")
                                {
                                    glm::mat4 M = entity->localTransform.toMat4();
                                    glm::vec3 front = glm::vec3(M * glm::vec4(0, 0, -1, 0));

                                    // undo last move
                                    //
                                    position -= deltaTime * movement->linearVelocity * front;
                                    rotation.y += glm::radians(180.0f);
                                }
                            }

                            if (entity->name == "hand")
                                if (otherEntity->name == "spider")
                                {
                                    if (!postprocessEffect)
                                    {
                                        lives -= 1;
                                        Entity *player = world->GetEntity("player");
                                        PlayerComponent *playerComponent = player->getComponent<PlayerComponent>();

                                        if (lives == 0)
                                            notify(Event::PLAYER_CAUGHT_BY_GRANNY);

                                        time = 0;
                                        text = "spiders the may kill you....they smell your fear";
                                        notify(Event::TERRIFIED);
                                        postprocessEffect = true;
                                        renderer->changeApply(true);
                                    }
                                }

                            if (entity->name == "spider")
                            {

                                glm::mat4 M = entity->localTransform.toMat4();
                                glm::vec3 front = glm::vec3(M * glm::vec4(0, 0, -1, 0));

                                // undo last move
                                //
                                position -= deltaTime * movement->linearVelocity * front;
                                rotation.y += glm::radians(90.0f) + glm::radians((std::rand() % 181) * 1.0f);
                                // entity->localTransform.rotation.y += glm::radians((std::rand() % 181) * 1.0f);
                                continue;
                            }

                            // if (entity->name == "hand")
                            // {
                            //     if (otherEntity->name == "granny")
                            //         renderer->changeApply(true);
                            // }

                            if (entity->name == "granny")
                     {           
                      
                            time1 = 0;
                                glm::mat4 M = entity->localTransform.toMat4();
                                glm::vec3 front = glm::vec3(M * glm::vec4(0, 0, -1, 0));

                                // undo last move
                                //
                            entity->localTransform.position[0] -= deltaTime * movement->linearVelocity[0] * front[0];
                            entity->localTransform.position[1] =10.4;
                            
                            entity->localTransform.position[2] -= deltaTime * movement->linearVelocity[2] * front[2];
                        
                    //      if (time2 < 100)
                    //     {
                    //         time2= 0;
                    //             glm::mat4 M = entity->localTransform.toMat4();    
                            rotation.y += glm::radians(90.0f) + glm::radians((std::rand() % 181) * 1.0f);
                                // entity->localTransform.rotation.y += glm::radians((std::rand() % 181) * 1.0f);
                                continue;
                        
                        //  if (time2 > 200)
                        // {
                        //     time2= 0;

                        //       glm::mat4 M = entity->localTransform.toMat4();
                        //         glm::vec3 front = glm::vec3(M * glm::vec4(0, 0, -1, 0));

                        //         // undo last move
                        //         //
                        //     entity->localTransform.position[0] -= deltaTime * movement->linearVelocity[0] * front[0];
                        //     entity->localTransform.position[1]=7.5 ;
                        //     entity->localTransform.position[2] -= deltaTime * movement->linearVelocity[2] * front[2];
                                
                        //     rotation.y += glm::radians(90.0f) + glm::radians((std::rand() % 181) * 1.0f);
                        //         // entity->localTransform.rotation.y += glm::radians((std::rand() % 181) * 1.0f);
                        //         continue;
                        

                        // if (time3 > 300)
                        // {
                        // time3= 0;
                        //    glm::mat4 M = entity->localTransform.toMat4();
                        //         glm::vec3 front = glm::vec3(M * glm::vec4(0, 0, -1, 0));

                        //         // undo last move
                        //         //
                        //     entity->localTransform.position[0] -= deltaTime * movement->linearVelocity[0] * front[0];
                        //     entity->localTransform.position[1]=4.7 ;
                        //     entity->localTransform.position[2] -= deltaTime * movement->linearVelocity[2] * front[2];
                                
                        //     rotation.y += glm::radians(90.0f) + glm::radians((std::rand() % 181) * 1.0f);
                        //         // entity->localTransform.rotation.y += glm::radians((std::rand() % 181) * 1.0f);
                        //         continue;
                        // } 

                            }
                            if (otherEntity->name == "coins")
                            {
                                // notify player to increament counter
                                continue;
                            }

                            // firing event to notify key1 is found  (testing)
                            if (otherEntity->name == "drawer")
                            {
                                text = "you may need a heavy tool to open it";
                                notify(Event::DRAWER_COLLISION);
                                continue;
                            }
                            if (otherEntity->name == "screw")
                            {
                                text = "this screw might be helpfull for openning doors";
                                notify(Event::SCREW_FOUND);
                                continue;
                            }
                            if (otherEntity->name == "key1")
                            {
                                text = "search for the required door";
                                notify(Event::KEY1_FOUND);
                                continue;
                            }
                            if (otherEntity->name == "key2")
                            {
                                notify(Event::KEY2_FOUND);
                                continue;
                            }
                            if (otherEntity->name == "key3")
                            {
                                notify(Event::KEY3_FOUND);
                                continue;
                            }
                            if (otherEntity->name == "key4")
                            {
                                notify(Event::KEY4_FOUND);
                                continue;
                            }
                            if (otherEntity->name == "key5")
                            {
                                notify(Event::KEY5_FOUND);
                                continue;
                            }
                            if (otherEntity->name == "hummer")
                            {
                                notify(Event::HUMMER_FOUND);
                                continue;
                            }
                            if (otherEntity->name == "key6")
                            {
                                notify(Event::KEY6_FOUND);
                                continue;
                            }
                        }
                    }
                }
            }
            return std::make_pair(text, lives);
        }
    };
}
