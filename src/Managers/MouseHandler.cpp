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

void MouseHandler::render_colors() {
    color_map->begin_drawing_color();
    auto it = color_lookup.begin();
    while(it != color_lookup.end()) {
        if(auto renderable_object = it->second.lock()) {
            color_map->set_active_color(it->first);
            renderable_object->render_to_color_map(*color_map);
            it++;
        }
        else{
            it = color_lookup.erase(it);
        }
    }
    color_map->finish_drawing_color();
}

void MouseHandler::register_subscriber(std::weak_ptr<MouseSubscriber> subscriber) {
    sf::Color rand_color;
    
    do {
        rand_color = sf::Color(rand()%255+1,rand()%255+1,rand()%255+1);
    } while (color_lookup.contains(rand_color));

    color_lookup[rand_color] = subscriber;
}

std::optional<std::shared_ptr<MouseSubscriber>> MouseHandler::get_object_at_mouse_position(int x, int y) {
    render_colors();
    auto color = color_map->get_color_at_world({x,y});

    if(color) {
        if (auto obj = color_lookup[color.value()].lock())
            return obj;
    }

    return {};
}

void MouseHandler::handle_press(sf::Event &event) {
    if (auto obj = get_object_at_mouse_position(event.mouseButton.x, event.mouseButton.y)) {
        auto unwrapped_obj = obj.value();
        dragged_object = unwrapped_obj;
        unwrapped_obj->handle_press(event);
    }
}

void MouseHandler::handle_move(sf::Event &event) {
    if (auto obj = get_object_at_mouse_position(event.mouseMove.x, event.mouseMove.y))
        obj.value()->handle_move(event);
    
    if(auto obj = dragged_object.lock()) {
        obj->handle_drag(event);
    }
}

void MouseHandler::handle_release(sf::Event &event) {
    if (auto obj = get_object_at_mouse_position(event.mouseButton.x, event.mouseButton.y))
        obj.value()->handle_release(event);

    if(auto obj = dragged_object.lock()) {
        obj->handle_drag_end(event);
        dragged_object.reset();
    }
}