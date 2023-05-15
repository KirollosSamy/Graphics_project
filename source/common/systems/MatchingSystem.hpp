#pragma once

#include "system.hpp"
#include "../ecs/world.hpp"
#include "../application.hpp"

namespace our
{
    // The Pick system is responsible for droping objects in the world
    class MatchingSystem : public System
    {    
    public:
        std::string tool = "";
        void Matching(World *world);
        
    };
}

