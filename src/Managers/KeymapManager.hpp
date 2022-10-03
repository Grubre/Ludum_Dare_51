#pragma once
#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>
#include <map>
#include <functional>

class KeymapManager{
public:
    void register_keymap(sf::Keyboard::Key key, const std::function<void()>& func);
    void unregister_keymap(sf::Keyboard::Key key);
    void check_keypresses();

    static KeymapManager* get_instance();

private:
    KeymapManager() = default;
    std::map<sf::Keyboard::Key, std::vector<std::function<void()>>> keymaps;

    static KeymapManager* m_instance;
};
