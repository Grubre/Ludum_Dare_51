#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Standard/math.hpp"
#include "Standard/event.hpp"
#include "Nodes/Node.hpp"
#include "Nodes/TestingShape.hpp"
#include "Nodes/Enemy.hpp"

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
  sf::RenderWindow window(sf::VideoMode(w, h), "SFML window");

  window.setVerticalSyncEnabled(true);
  sf::Clock delta_clock;

  auto layers = Layers::get_instance();

  layers->add_layer(window, "GUI");
  layers->add_layer(window, "Objects");

  std::shared_ptr<Node> root = Node::create<Node>();

  std::shared_ptr<TestingShape> ts = TestingShape::create<TestingShape>();

  std::shared_ptr<Enemy> orc = Enemy::create<Enemy>("Orc1", 0.5, 0.5, 0.5, 0.5, "hitHurt.wav", "explosion.wav", 700, 120);
  orc->setScale(5);

  bool MouseLeftPressed = false;
  bool MouseRightPressed = false;

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

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
      if(!MouseLeftPressed)
      {
        MouseLeftPressed = true;
        orc->addNewWaypoint({(float)sf::Mouse::getPosition(window).x , (float)sf::Mouse::getPosition(window).y});
      }
    }
    else
    {
      MouseLeftPressed = false;
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    {
      if(!MouseRightPressed)
      {
        MouseRightPressed = true;
        orc->takeDamage(10);
      }
    }
    else
    {
      MouseRightPressed = false;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
      orc->stopMoving();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
      orc->startMoving();
    }

    // Testing code
    ts->draw();

    // Update the window
    orc->update(delta);
    orc->draw();

    layers->draw_all_layers(window);
    window.display();
  }
  return EXIT_SUCCESS;
}
