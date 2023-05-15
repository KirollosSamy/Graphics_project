#pragma once

namespace our {
    // This enum holds all the possible events in the game
    // Each event should be fired by at most one system and handled by at least one system (1 to many).
    enum class Event {
        // comments are in the form: firing system => listener system(s)

        KEY_FOUND, //collision system => player system
        PLAYER_CAUGHT_BY_GRANNY, // granny system => player system
        PLAYER_AT_DOOR, //collision system => player system
        FOUND_COIN, //collision system => player system
        MADE_NOISE, //collision system => granny system
        KEY1_FOUND,
        KEY2_FOUND,
        KEY3_FOUND,
        DOOR1_COLLISION,
        DOOR2_COLLISION,
        DOOR3_COLLISION,
        COLLISION_WITH_WALL,
        TERRIFIED,
        NORMAL_MUSIC,
        RUNNING,
    };
}
