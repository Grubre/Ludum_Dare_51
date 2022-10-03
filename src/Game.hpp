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
        curr_scene = (Scene*)mainMenuScene;

        sfEventManager->register_event(sf::Event::Closed, [this](sf::Event&){
                renderer.close();
        });
    }

    void start()
    {
        sf::Clock delta_clock;

      auto ts = TestingShape::create<TestingShape>();

      ts->setTranslation({600, 300});

      MouseHandler::initialize(renderer.get_color_map());
      MouseHandler::get_instance()->register_subscriber(ts);

      while (renderer.is_open()) {
        sfEventManager->poll_events(renderer);
        
        keymapManager->check_keypresses();

        sf::Time delta = delta_clock.restart();
        
        curr_scene->update(delta);
        
        renderer.begin_drawing();

        ts->draw(renderer);

        curr_scene->draw();

        renderer.finish_drawing();        
      }
    }
};
