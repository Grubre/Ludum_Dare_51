#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Standard/math.hpp"
#include "Standard/event.hpp"
#include "Nodes/Node.hpp"
#include "Nodes/TestingShape.hpp"
#include "Nodes/Enemy.hpp"
#include "Renderer/Renderer.hpp"
#include "Nodes/Wave.hpp"
#include "Nodes/Grid.hpp"
#include "Standard/KeymapManager.hpp"
#include "Nodes/SortNode.hpp"

#include <cstdint>
#include "Music/All.hpp"
#include "Animation/All.hpp"


int main() {
  constexpr uint32_t w = 1300, h = 800;
  // Create the main window
  Renderer renderer(w, h);
 
  MusicSystem *musicSystem = MusicSystem::getInstance("assets/Music/");
  SoundSystem *soundSystem = SoundSystem::getInstance("assets/Sounds/");

  musicSystem->playMusic("xDeviruchi - Minigame.wav");
  musicSystem->setVolume("xDeviruchi - Minigame.wav", 0.3);
  soundSystem->playSound("blipSelect.wav");

  AnimationLoaderPrototypeFactory::getInstance("assets/Textures/");


  sf::Clock delta_clock;

  std::shared_ptr<Node> root = Node::create<Node>();

  auto ysort = YSort::create<YSort>();

  std::shared_ptr<Wave> test = Wave::create<Wave>(ysort, sf::Vector2f(100, 100));
  test->addEnemy("Orc1", 30);
  test->addWaypoint({100, 500});
  test->addWaypoint({300, 500});
  test->addWaypoint({300, 200});
  test->addWaypoint({700, 200});
  test->addWaypoint({700, 600});
  test->addWaypoint({100, 600});
  test->addWaypoint({100, 700});
  test->addWaypoint({1200, 700});
  Grid grid({50,50}, "./assets/Tilesets/outdoors.png", {16,16});

  grid.setScale({5,5});

  KeymapManager keymapManager{};
  keymapManager.register_keymap(sf::Keyboard::Num1, [&test](){test->TurnOnWave();});
  keymapManager.register_keymap(sf::Keyboard::Num2, [&test](){test->TurnOffWave();});

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
    ysort->update(delta);
    grid.draw(renderer);
    ysort->draw(renderer);

    keymapManager.check_keypresses();

    renderer.finish_drawing();
  }
  return EXIT_SUCCESS;
}
