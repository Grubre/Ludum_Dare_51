#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Standard/math.hpp"
#include "Standard/event.hpp"
#include "Nodes/Node.hpp"
#include "Nodes/TestingShape.hpp"
#include "Renderer/Renderer.hpp"

#include <cstdint>
#include "Music/All.hpp"
#include "Animation/All.hpp"

int main() {
#ifdef DEBUG
  MusicSystem *musicSystem = MusicSystem::getInstance("assets/Music/");
  SoundSystem *soundSystem = SoundSystem::getInstance("assets/Sounds/");

  musicSystem->playMusic("xDeviruchi - Minigame.wav");
  musicSystem->setVolume("xDeviruchi - Minigame.wav", 20);
  soundSystem->playSound("blipSelect.wav");

  TextureLoaderPrototypeFactory::getInstance("assets/Textures/");
  sf::RectangleShape test({200, 200});
  test.setPosition(300, 300);
  AnimationManager testAnimationManager("Orc3", {{"idle", 0.25}, {"run", 0.25}}, "run");
#endif

  constexpr uint32_t w = 800, h = 600;
  // Create the main window
  Renderer renderer(w, h);

  sf::Clock delta_clock;

  std::shared_ptr<Node> root = Node::create<Node>();

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
    ts->draw(renderer);

    // Update the window
#ifdef DEBUG
    testAnimationManager.update(delta, false);
    test.setTexture(testAnimationManager.getTexture().get());
    test.setTextureRect(testAnimationManager.getIntRect());
#endif
    
    renderer.finish_drawing();
  }
  return EXIT_SUCCESS;
}
