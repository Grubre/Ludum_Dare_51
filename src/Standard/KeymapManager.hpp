#pragma once
#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>
#include <map>
#include <functional>

class KeymapManager{
public:
    void register_keymap(sf::Keyboard::Key key, const std::function<void()>& func){
        keymaps[key] = func;
    }
    void unregister_keymap(sf::Keyboard::Key key){
        keymaps.erase(key);
    }
    void check_keypresses(){
        for(const auto&[key, val] : keymaps)
            if(sf::Keyboard::isKeyPressed(key))
                val();
    }

private:
    std::map<sf::Keyboard::Key, std::function<void()>> keymaps;

};
