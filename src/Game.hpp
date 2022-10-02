#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Scenes/MainMenuScene.hpp"
#include "Standard/math.hpp"
#include "Standard/event.hpp"
#include "Nodes/Node.hpp"
#include "Nodes/TestingShape.hpp"
#include "Nodes/Enemy.hpp"
#include "Renderer/Renderer.hpp"
#include "Nodes/LevelWaves.hpp"
#include "Nodes/Grid.hpp"
#include "Standard/KeymapManager.hpp"
#include "Nodes/SortNode.hpp"
#include "Loaders/ResourceLoader.hpp"
#include "GUI/Text.hpp"
#include "Standard/config.hpp"
#include "Scenes/Scene.hpp"

#include <cstdint>
#include "Music/All.hpp"
#include "Animation/All.hpp"

class Game{
    MusicSystem *musicSystem;
    SoundSystem *soundSystem;
    ResourceLoader *resourceLoader;
    Renderer renderer;
    KeymapManager* keymapManager;

    Scene* curr_scene;
    MainMenuScene* mainMenuScene;

public:
    Game(const uint32_t window_width, const uint32_t window_height) :
        musicSystem(MusicSystem::getInstance("assets/Music/")),
        soundSystem(SoundSystem::getInstance("assets/Sounds/")),
        resourceLoader(ResourceLoader::get_instance()),
        renderer(window_width, window_height),
        keymapManager(KeymapManager::get_instance())
    {
        LevelWaves::setDirectory("assets/Levels/");
        AnimationLoaderPrototypeFactory::getInstance("assets/Textures/");
        resourceLoader->load_font("arial.ttf");
        mainMenuScene = new MainMenuScene(renderer, &curr_scene);
    }

    void loop()
    {
      sf::Clock delta_clock;



      while (renderer.is_open()) {
        poll_events();

        sf::Time delta = delta_clock.restart();
        
        renderer.begin_drawing();

        mainMenuScene->draw();
        mainMenuScene->update(delta);

        renderer.finish_drawing();

        keymapManager->check_keypresses();
      }
    }

private:
    void poll_events()
    {
        sf::Event event{};
        while (renderer.poll_event(event)) {
          // Close window: exit
        if (event.type == sf::Event::Closed)
            renderer.close();
        }
    }
};
