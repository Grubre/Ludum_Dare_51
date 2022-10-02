#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <memory>
#include "Layers.hpp"

Layers* Layers::m_instance = nullptr;

using layer_ptr = std::shared_ptr<sf::RenderTexture>;

Layers* Layers::get_instance()
{
    if(m_instance == nullptr)
        m_instance = new Layers();
    return m_instance;
}

void Layers::add_layer(const sf::RenderWindow &window, std::string name)
{
    layer_ptr layer = std::make_shared<sf::RenderTexture>();

    layer->create(window.getSize().x,window.getSize().y);

    if(m_mappings.contains(name))
    {
        name = name + std::to_string(m_mappings.count(name) + 1);
    }

    m_mappings[name] = layer;
    m_layers.push_back(layer);
}
layer_ptr Layers::get_layer(unsigned long id) const
{
    // we return the furthest layer
    id = std::min((unsigned long)m_layers.size() - 1, id);
    return m_layers[id];
}
layer_ptr Layers::get_layer(const std::string &name) const
{
    return m_mappings.at(name);
}
std::vector<layer_ptr>& Layers::get_layers() { return m_layers; }

layer_ptr Layers::operator[](unsigned long id) const
{
    return get_layer(id);
}
layer_ptr Layers::operator[](const std::string& name) const
{
    return get_layer(name);
}

void Layers::clear_all_layers() {
    for(int i = m_layers.size()-1; i >= 0; i--)
    {
        m_layers[i]->clear(sf::Color(0,0,0,0));
    }
}

void Layers::draw_all_layers(sf::RenderWindow& window) {
    for(int i = m_layers.size()-1; i >= 0; i--)
    {
        m_layers[i]->display();
        window.draw(sf::Sprite(m_layers[i]->getTexture()));
    }
}

// Przydałoby się, ale jeszcze nie wiem jak 
// void Layers::resize_all_layers(const sf::RenderWindow& window) {
//     for(int i = m_layers.size()-1; i >= 0; i--)
//     {
//      
//     }
//}



