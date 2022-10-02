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
#include "Managers/KeymapManager.hpp"
#include "Managers/SFEventManager.hpp"
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
    SFEventManager* sfEventManager;

    Scene* curr_scene;
    MainMenuScene* mainMenuScene;

public:
    Game(const uint32_t window_width, const uint32_t window_height) :
        musicSystem(MusicSystem::getInstance("assets/Music/")),
        soundSystem(SoundSystem::getInstance("assets/Sounds/")),
        resourceLoader(ResourceLoader::get_instance()),
        renderer(window_width, window_height),
        keymapManager(KeymapManager::get_instance()),
        sfEventManager(SFEventManager::get_instance())
    {
        LevelWaves::setDirectory("assets/Levels/");
        AnimationLoaderPrototypeFactory::getInstance("assets/Textures/");
        resourceLoader->load_font("arial.ttf");
        mainMenuScene = new MainMenuScene(renderer, &curr_scene);

        sfEventManager->register_event(sf::Event::Closed, [this](){
                renderer.close();
        });
        sfEventManager->register_event(sf::Event::MouseButtonPressed, [](){
                std::cout << "Mouse pressed!\n";
        });
    }

    void loop()
    {
      sf::Clock delta_clock;

      while (renderer.is_open()) {
        sfEventManager->poll_events(renderer);
        
        keymapManager->check_keypresses();

        sf::Time delta = delta_clock.restart();
        
        mainMenuScene->update(delta);
        
        renderer.begin_drawing();

        mainMenuScene->draw();

        renderer.finish_drawing();

      }
    }
};
