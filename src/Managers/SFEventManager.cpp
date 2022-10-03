#include "SFEventManager.hpp"
#include <iostream>


SFEventManager* SFEventManager::m_instance = nullptr;

void SFEventManager::register_event(sf::Event::EventType event, const std::function<void()>& func){
    events[event].push_back(func);
}
void SFEventManager::unregister_event(sf::Event::EventType event){
    events.erase(event);
}
void SFEventManager::poll_events(Renderer& renderer) const{
    sf::Event event{};
    while (renderer.poll_event(event)) {
        for(auto[key, val] : events)
        {
            if(event.type == key)
                for(auto& callback : val)
                    callback();
        }
    }
}

 SFEventManager* SFEventManager::get_instance(){
    if(m_instance == nullptr)
        m_instance = new SFEventManager();
    return m_instance;
}
