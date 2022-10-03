#include "KeymapManager.hpp"
#include <iostream>

KeymapManager* KeymapManager::m_instance = nullptr;

void KeymapManager::register_keymap(sf::Keyboard::Key key, const std::function<void()>& func){
    keymaps[key].push_back(func);
}
void KeymapManager::unregister_keymap(sf::Keyboard::Key key){
    keymaps.erase(key);
}
void KeymapManager::check_keypresses(){
    for(auto[key, val] : keymaps)
    {
        if(sf::Keyboard::isKeyPressed(key))
            for(auto& callback : val)
                callback();
    }
}

 KeymapManager* KeymapManager::get_instance(){
    if(m_instance == nullptr)
        m_instance = new KeymapManager();
    return m_instance;
}
