#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Standard/math.hpp"
#include "Standard/event.hpp"
#include "Nodes/Node.hpp"
#include "Nodes/TestingShape.hpp"
#include "Nodes/Enemy.hpp"
#include "Renderer/Renderer.hpp"
#include "Nodes/Wave.hpp"

#include <cstdint>
#include "Music/All.hpp"
#include "Animation/All.hpp"


int main() {
  MusicSystem *musicSystem = MusicSystem::getInstance("assets/Music/");
  SoundSystem *soundSystem = SoundSystem::getInstance("assets/Sounds/");

  musicSystem->playMusic("xDeviruchi - Minigame.wav");
  musicSystem->setVolume("xDeviruchi - Minigame.wav", 0.3);
  soundSystem->playSound("blipSelect.wav");

  TextureLoaderPrototypeFactory::getInstance("assets/Textures/");

  constexpr uint32_t w = 1300, h = 800;
  // Create the main window
  Renderer renderer(w, h);

  sf::Clock delta_clock;

  std::shared_ptr<Node> root = Node::create<Node>();

  std::shared_ptr<Wave> test = Wave::create<Wave>(sf::Vector2f(100, 100));
  test->addEnemy("Orc1", 30);
  test->addWaypoint({100, 500});
  test->addWaypoint({300, 500});
  test->addWaypoint({300, 200});
  test->addWaypoint({700, 200});
  test->addWaypoint({700, 600});
  test->addWaypoint({100, 600});
  test->addWaypoint({100, 700});
  test->addWaypoint({1200, 700});

  while (renderer.is_open()) {
    // Process events
    sf::Event event{};
    while (renderer.poll_event(event)) {
      // Close window: exit
      if (event.type == sf::Event::Closed)
        renderer.close();
    }

    sf::Time delta = delta_clock.restart();

   test->update(delta);

   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
   {
    test->TurnOnWave();
   }

   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
   {
    test->TurnOffWave();
   }

    renderer.begin_drawing();
    test->draw(renderer);
    renderer.finish_drawing();
  }
  return EXIT_SUCCESS;
}
