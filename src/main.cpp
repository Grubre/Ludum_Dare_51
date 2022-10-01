#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Standard/math.hpp"
#include "Standard/event.hpp"
#include "Nodes/Node.hpp"
#include "Nodes/TestingShape.hpp"

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
  sf::RenderWindow window(sf::VideoMode(w, h), "SFML window");

  window.setVerticalSyncEnabled(true);
  sf::Clock delta_clock;

  auto layers = Layers::get_instance();

  layers->add_layer(window, "GUI");
  layers->add_layer(window, "Objects");

  std::shared_ptr<Node> root = Node::create<Node>();

  std::shared_ptr<TestingShape> ts = TestingShape::create<TestingShape>();

  while (window.isOpen()) {
    // Process events
    sf::Event event{};
    while (window.pollEvent(event)) {
      // Close window: exit
      if (event.type == sf::Event::Closed)
        window.close();
    }

    sf::Time delta = delta_clock.restart();
    
    // Clear screen
    window.clear();
    layers->clear_all_layers(); 

    // Testing code
    ts->draw();

    // Update the window
#ifdef DEBUG
    testAnimationManager.update(delta, false);
    test.setTexture(testAnimationManager.getTexture().get());
    test.setTextureRect(testAnimationManager.getIntRect());
    window.draw(test);
#endif
    layers->draw_all_layers(window);
    window.display();
  }
  return EXIT_SUCCESS;
}
