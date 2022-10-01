#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdint>
#include "Music/MusicSystem.hpp"
#include "Music/SoundSystem.hpp"

int main() {
#ifdef DEBUG
  MusicSystem *musicSystem = MusicSystem::getInstance("assets/Music/");
  SoundSystem *soundSystem = SoundSystem::getInstance("assets/Sounds/");

  musicSystem->playMusic("xDeviruchi - Minigame.wav");
  soundSystem->playSound("blipSelect.wav");
#endif
  constexpr uint32_t w = 800, h = 600;
  // Create the main window
  sf::RenderWindow window(sf::VideoMode(w, h), "SFML window");
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
    window.display();
  }
  return EXIT_SUCCESS;
}
