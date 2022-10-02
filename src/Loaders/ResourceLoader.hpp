#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <unordered_map>

class ResourceLoader
{
public:
    using font_ptr = std::shared_ptr<sf::Font>;
    using texture_ptr = std::shared_ptr<sf::Texture>;

    font_ptr get_font(unsigned int index);
    texture_ptr get_texture(const std::string &name);
    void load_font(const std::string &name);
    void load_texture(const std::string &path);

    static ResourceLoader* get_instance();
private:
    std::vector<font_ptr> fonts;
    std::unordered_map<std::string, texture_ptr> textures; 

    static ResourceLoader* m_instance;
};