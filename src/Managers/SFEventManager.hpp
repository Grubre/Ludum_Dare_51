#pragma once
#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>
#include <map>
#include <functional>
#include "Renderer/Renderer.hpp"

// inline static auto event_compare = [](const sf::Event& x, const sf::Event& y){
//     return x.type < y.type;
// };

class SFEventManager{
public:
    void register_event(sf::Event::EventType event, const std::function<void()>& func);
    void unregister_event(sf::Event::EventType event);
    void poll_events(Renderer& renderer) const;

    static SFEventManager* get_instance();

private:
    SFEventManager() = default;
    std::map<sf::Event::EventType, std::function<void()>> events;

    static SFEventManager* m_instance;
};
