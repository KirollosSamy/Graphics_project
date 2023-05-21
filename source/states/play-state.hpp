#pragma once

#include <application.hpp>

#include <ecs/world.hpp>
#include <systems/forward-renderer.hpp>
#include <systems/free-camera-controller.hpp>
#include <systems/movement.hpp>
#include <systems/collision.cpp>
#include <asset-loader.hpp>
#include <systems/player-system.hpp>
#include <systems/PickSystem.hpp>
#include <systems/DropSystem.hpp>
#include <systems/MatchingSystem.hpp>
#include <systems/granny-system.hpp>

// #include <systems/sound.hpp>
#include <systems/sound.hpp>

// This state shows how to use the ECS framework and deserialization.
class Playstate : public our::State
{

    std::string text;
    our::World world;
    std::pair<std::string, int> message;

    our::ForwardRenderer renderer;
    our::FreeCameraControllerSystem cameraController;
    our::MovementSystem movementSystem;

    our::PlayerSystem playerSystem;
    // our::GrannySystem grannySystem;
    // our::ObjectSystem objectSystem;
    our::CollisionSystem collisionSystem;
    our::PickSystem pickSystem;
    our::DropSystem dropSystem;
    our::MatchingSystem matchingSystem;
    our::GrannySystem grannySystem;
    // our::SoundSystem soundSystem;
    our::SoundSystem soundSystem;

    void onInitialize() override
    {
        text = "You thought you were alone... You were wrong.";
        // First of all, we get the scene configuration from the app config
        auto &config = getApp()->getConfig()["scene"];
        // If we have assets in the scene config, we deserialize them
        if (config.contains("assets"))
        {
            our::deserializeAllAssets(config["assets"]);
        }
        // If we have a world in the scene config, we use it to populate our world
        if (config.contains("world"))
        {
            world.deserialize(config["world"]);
        }
        // We initialize the camera controller system since it needs a pointer to the app
        cameraController.enter(getApp());
        // Then we initialize the renderer
        auto size = getApp()->getFrameBufferSize();
        renderer.initialize(size, config["renderer"], &world);

        // search for the player once for efficiency
        // bool playerExist = playerSystem.setPlayer(&world);
        // if(!playerExist) getApp()->changeState("menu");

        // setting soundEngine pointer

        pickSystem.setApp(getApp());
        dropSystem.setApp(getApp());
        collisionSystem.setApp(getApp());
        soundSystem.setSoundEngine(getApp()->getSoundEngine());

        setEventListeners();
    }

    void onDraw(double deltaTime) override
    {
        // Here, we just run a bunch of systems to control the world logic
        movementSystem.update(&world, (float)deltaTime);                       // monkey up
        cameraController.update(&world, (float)deltaTime);                     // p = p + delta x(z,y,w)  collision -> false  || collision -> true
        message = collisionSystem.update(&world, (float)deltaTime, &renderer); //  == p - delta x
        soundSystem.update(&world);
        pickSystem.update(&world);
        dropSystem.Drop(&world);
        matchingSystem.Matching(&world);
        // grannySystem.update(&world,(float)deltaTime);
        // objectSystem.update(&world);
        // grannySystem.update(&world);

        our::GameStatus gameStatus = playerSystem.update(&world);

        // check if the game has ended
        // we can modify menu state slightly to display gameover and won screen.
        if (gameStatus == our::GameStatus::WON)
            getApp()->changeState("menu");
        else if (gameStatus == our::GameStatus::LOST)
            getApp()->changeState("menu");

        // And finally we use the renderer system to draw the scene
        renderer.render(&world);

        // Get a reference to the keyboard object
        auto &keyboard = getApp()->getKeyboard();

        if (keyboard.justPressed(GLFW_KEY_ESCAPE))
        {
            // If the escape  key is pressed in this frame, go to the play state
            getApp()->changeState("menu");
        }
    }

    void onDestroy() override
    {
        // Don't forget to destroy the renderer
        renderer.destroy();
        // On exit, we call exit for the camera controller system to make sure that the mouse is unlocked
        cameraController.exit();
        // Clear the world
        world.clear();
        // and we delete all the loaded assets to free memory on the RAM and the VRAM
        our::clearAllAssets();
    }

    // All the dependecies between systems should be listed here
    void setEventListeners()
    {
        playerSystem.listen(&collisionSystem);
        pickSystem.listen(&collisionSystem);
        matchingSystem.listen(&collisionSystem);
        // TODO :
        playerSystem.listen(&grannySystem);

        // soundSystem.listen(&collisionSystem);
        soundSystem.listen(&collisionSystem);

        // playerSystem.listen(&objectSystem);
    }
    void onImmediateGui() override
    {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        // Box 1
        ImGui::SetNextWindowPos(ImVec2(20, 20)); // Set position of Box 1
        ImGui::Begin("Box1", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
        ImGui::SetWindowSize(ImVec2(130, 80));
        ImGui::SetWindowFontScale(3.0f);
        ImGui::TextColored(ImVec4(1.0, 1.0, 1.0, 1.0), "Lives: ");
        ImGui::End();

        // // Box 2
        ImGui::SetNextWindowPos(ImVec2(150, 20)); // Set position of Box 2
        ImGui::Begin("Box2", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
        ImGui::SetWindowSize(ImVec2(100, 50));
        ImGui::SetWindowFontScale(3.0f);
        ImGui::TextColored(ImVec4(1.0, 1.0, 1.0, 1.0), std::to_string(message.second).c_str());
        ImGui::End();

        // Box 3
        ImVec2 screenCenter = ImVec2(ImGui::GetIO().DisplaySize.x / 2, 0);
        ImGui::SetNextWindowPos(screenCenter, ImGuiCond_Always, ImVec2(0.5f, 0.0f));
        ImGui::Begin("Box3", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
        ImGui::SetWindowSize(ImVec2(800, 50));
        ImGui::SetWindowFontScale(2.0f);
        ImGui::TextColored(ImVec4(1.0, 1.0, 1.0, 1.0), message.first.c_str());
        ImGui::End();

        ImGui::PopStyleColor();
    }
};
