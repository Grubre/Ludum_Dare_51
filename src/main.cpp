#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
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
#ifdef DEBUG
  sf::Clock deltaTime;
#endif
  while (window.isOpen()) {
    // Process events
    sf::Event event{};
    while (window.pollEvent(event)) {
      // Close window: exit
      if (event.type == sf::Event::Closed)
        window.close();
    }
    // Clear screen
    window.clear();
    // Update the window
#ifdef DEBUG
    testAnimationManager.update(deltaTime.getElapsedTime(), false);
    test.setTexture(testAnimationManager.getTexture().get());
    test.setTextureRect(testAnimationManager.getIntRect());
    window.draw(test);
    deltaTime.restart();
#endif
    window.display();
  }
  return EXIT_SUCCESS;
}
