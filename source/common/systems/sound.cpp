#pragma once

#include "sound.hpp"

namespace our
{
    // this function changes the game sound based on the situation
    void SoundSystem::update(World *world)
    {
        while (!eventQueue.empty())
        {
            Event event = eventQueue.front();
            eventQueue.pop();

            switch (event)
            {
            case Event::TERRIFIED:
                std::cout << "event reached here" << std::endl;
                SoundEngine->stopAllSounds();
                SoundEngine->play2D("assets/audio/heart.mp3", false);


                
                break;
            }
        }
    }
}
