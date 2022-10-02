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

#include <cstdint>
#include "Music/All.hpp"
#include "Animation/All.hpp"


int main() {
  MusicSystem *musicSystem = MusicSystem::getInstance("assets/Music/");
  SoundSystem *soundSystem = SoundSystem::getInstance("assets/Sounds/");

  musicSystem->playMusic("xDeviruchi - Minigame.wav");
  musicSystem->setVolume("xDeviruchi - Minigame.wav", 0.3);
  soundSystem->playSound("blipSelect.wav");

  LevelWaves::setDirectory("assets/Levels/");
  AnimationLoaderPrototypeFactory::getInstance("assets/Textures/");

  constexpr uint32_t w = 1300, h = 800;
  // Create the main window
  Renderer renderer(w, h);

  sf::Clock delta_clock;

  std::shared_ptr<Node> root = Node::create<Node>();
  std::shared_ptr<LevelWaves> test = LevelWaves::create<LevelWaves>("level1.lvl");

  Grid grid({1,1}, "./assets/Tilesets/outdoors.png", {16,16});
  grid.setScale({5,5});

  KeymapManager keymapManager{};

  std::shared_ptr<TestingShape> ts = TestingShape::create<TestingShape>();

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

    grid.draw(renderer);
    test->draw(renderer);

    keymapManager.check_keypresses();

    renderer.finish_drawing();
  }
  return EXIT_SUCCESS;
}
