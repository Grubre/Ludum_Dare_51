#include "Loaders/ResourceLoader.hpp"
#include <memory>
#include <string>
#include <algorithm>
#include <iostream>

using font_ptr = std::shared_ptr<sf::Font>;

ResourceLoader* ResourceLoader::m_instance = nullptr;

font_ptr ResourceLoader::get_font(const std::string &name)
{
    if(!fonts.contains(name))
        return load_font(name);
    return fonts.at(name);
}

font_ptr ResourceLoader::load_font(const std::string &name)
{
    sf::Font font;
    if(!font.loadFromFile(fonts_path + name))
        std::cerr << "Failed to load [[" << name <<"]] font!" << std::endl;
    if(!fonts.contains(name))
        fonts[name] = std::make_shared<sf::Font>(font);
    return fonts.at(name);
}

ResourceLoader* ResourceLoader::get_instance()
{
    if(m_instance == nullptr)
        m_instance = new ResourceLoader();
    return m_instance;
}

using texture_ptr = std::shared_ptr<sf::Texture>;
texture_ptr ResourceLoader::get_texture(const std::string& name)
{
    return textures.at(name);
}

texture_ptr ResourceLoader::load_texture(const std::string& path)
{
    texture_ptr texture = std::make_shared<sf::Texture>();
    if(!texture->loadFromFile(path))
        std::cout << "Failed to load texture from: " << path << std::endl;
    auto pos = path.find_last_of('/');
    textures[path.substr(pos + 1, path.length())] = texture;
    return texture;
}
