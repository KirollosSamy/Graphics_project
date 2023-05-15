#pragma once

#include "system.hpp"
#include "../ecs/world.hpp"
#include "../application.hpp"



#include <irrKlang.h>
using namespace irrklang;



namespace our
{
    // The Pick system is responsible for picking objects in the world
    class SoundSystem : public System
    {
       Application *app;  
       ISoundEngine *SoundEngine;  
       
    public:
        // this function is used to set the application pointer to get keyboard
        void setSoundEngine(ISoundEngine * engine)
        {
            this->SoundEngine = engine;
        }

        void update(World *world);
    };
}

