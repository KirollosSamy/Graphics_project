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
                // std::cout << "event reached hereeeeeeeeeeee" << std::endl;
                // SoundEngine->stopAllSounds();
                // SoundEngine->play2D("assets/audio/14. Spotted.mp3", false);
                break;
            case Event::NORMAL_MUSIC:
                // SoundEngine->stopAllSounds();
                // SoundEngine->play2D("assets/audio/29. Another Evil.mp3", true);
                break;
                case Event::BADROOM:
                // SoundEngine->stopAllSounds();
                // SoundEngine->play2D("assets/audio/29. Another Evil.mp3", false);
                break;

            }
        }
    }
}
