#include <SFML/Graphics.hpp>
#include "Renderer.hpp"

using Layer = sf::RenderTexture;

void Renderer::Layers::add_layer(const sf::RenderWindow &window)
{
    m_layers.emplace_back();
    m_layers.back().create(window.getSize().x, window.getSize().y);
}
Layer* Renderer::Layers::get_layer(unsigned long id)
{
    return &m_layers[id];
}
Layer* Renderer::Layers::operator[](unsigned long id)
{
    return get_layer(id);
}

void Renderer::Layers::clear_all_layers() {
    for(int i = m_layers.size()-1; i >= 0; i--)
    {
        m_layers[i].clear(sf::Color(0,0,0,0));
    }
}

void Renderer::Layers::draw_all_layers(sf::RenderWindow& window) {
    for(int i = m_layers.size()-1; i >= 0; i--)
    {
        m_layers[i].display();
        window.draw(sf::Sprite(m_layers[i].getTexture()));
    }
}

void Renderer::Layers::resize_all_layers(const sf::RenderWindow& window) {
    for(int i = m_layers.size()-1; i >= 0; i--)
    {
        m_layers[i].create(window.getSize().x, window.getSize().y);
    }
}



