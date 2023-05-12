#pragma once

#include "system.hpp"
#include "../ecs/world.hpp"
#include "../application.hpp"

namespace our
{
    // The Pick system is responsible for droping objects in the world
    class DropSystem : public System
    {
       Application *app;    
    public:
        // This should be called every frame to apply the game logic.

        // this function is used to set the application pointer to get keyboard
        void setApp(Application *app)
        {
            this->app = app;
        }

        void Drop(World *world);
    };
}

