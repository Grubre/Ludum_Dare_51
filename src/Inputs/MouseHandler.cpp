#include "MouseHandler.hpp"
#include "Managers/SFEventManager.hpp"
#include <cassert>

MouseHandler* MouseHandler::m_instance = nullptr;

void MouseHandler::initialize(std::shared_ptr<ColorMap> color_map)
{
    m_instance = new MouseHandler(color_map);
}

MouseHandler::MouseHandler(std::shared_ptr<ColorMap> color_map)
  : color_map(color_map)
{
    SFEventManager::get_instance()->register_event(
      sf::Event::MouseButtonPressed, [this](sf::Event &event) { handle_press(event); });
    
    SFEventManager::get_instance()->register_event(
      sf::Event::MouseMoved, [this](sf::Event &event) { handle_move(event); });
    
    SFEventManager::get_instance()->register_event(
      sf::Event::MouseButtonReleased, [this](sf::Event &event) { handle_release(event); });
}

MouseHandler* MouseHandler::get_instance()
{
    assert(m_instance != nullptr);
    return m_instance;
}

void MouseHandler::handle_press(sf::Event &event) {

}

void MouseHandler::handle_move(sf::Event &event) {

}

void MouseHandler::handle_release(sf::Event &event) {

}