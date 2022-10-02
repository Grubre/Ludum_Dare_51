#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
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

#include <cstdint>
#include "Music/All.hpp"
#include "Animation/All.hpp"

class Game{
    MusicSystem *musicSystem;
    SoundSystem *soundSystem;
    ResourceLoader *resourceLoader;
    Renderer renderer;
    KeymapManager keymapManager;

public:
    Game(const uint32_t window_width, const uint32_t window_height) :
        musicSystem(MusicSystem::getInstance("assets/Music/")),
        soundSystem(SoundSystem::getInstance("assets/Sounds/")),
        resourceLoader(ResourceLoader::get_instance()),
        renderer(window_width, window_height)
    {
        LevelWaves::setDirectory("assets/Levels/");
        AnimationLoaderPrototypeFactory::getInstance("assets/Textures/");
        resourceLoader->load_font("arial.ttf");
    }

    void loop()
    {
      sf::Clock delta_clock;
      auto TESTMAINysort = YSort::create<YSort>();

      std::shared_ptr<Node> root = Node::create<Node>();
      std::shared_ptr<LevelWaves> test = LevelWaves::create<LevelWaves>(TESTMAINysort, "level1.lvl");

      Grid grid({1,1}, "./assets/Tilesets/outdoors.png", {16,16});

      grid.setScale({5,5});

      keymapManager.register_keymap(sf::Keyboard::Num1, [&test](){test->nextWave();});

      std::shared_ptr<TestingShape> ts = TestingShape::create<TestingShape>();

      auto text = Text::create<Text>(resourceLoader->load_font("arial.ttf") , "TEST");
      text->text().setStyle(sf::Text::Bold | sf::Text::Italic);
      // text->setCharacterSize(50);

      while (renderer.is_open()) {
        // Process events
        sf::Event event{};
        while (renderer.poll_event(event)) {
          // Close window: exit
        if (event.type == sf::Event::Closed)
            renderer.close();
        }

        sf::Time delta = delta_clock.restart();
        
        // Clear screen
        renderer.begin_drawing();
        // Testing code
        test->update(delta);
        TESTMAINysort->update(delta);

        test->draw(renderer);
        grid.draw(renderer);

        text->draw(renderer);
        TESTMAINysort->draw(renderer);

        keymapManager.check_keypresses();

        renderer.finish_drawing();
      }
    }
};
