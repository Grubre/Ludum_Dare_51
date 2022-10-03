#include <SFML/Graphics.hpp>
#include <iostream>
#include "Renderer.hpp"

using Layer = sf::RenderTexture;

void Renderer::Layers::add_layer(const sf::RenderWindow &window)
{
    m_layers.emplace_back(new Layer());
    m_layers.back()->create(window.getSize().x, window.getSize().y);
}
Layer* Renderer::Layers::get_layer(unsigned long id)
{
    return m_layers[id];
}
Layer* Renderer::Layers::operator[](unsigned long id)
{
    return get_layer(id);
}

void Renderer::Layers::clear_all_layers() {
    for(int i = m_layers.size()-1; i >= 0; i--)
    {
        m_layers[i]->clear(sf::Color(0,0,0,0));
    }
}

void Renderer::Layers::draw_all_layers(sf::RenderWindow& window) {
    for(int i = m_layers.size()-1; i >= 0; i--)
    {
        m_layers[i]->display();
        window.draw(sf::Sprite(m_layers[i]->getTexture()));
    }   
}

void Renderer::Layers::resize_all_layers(const sf::RenderWindow& window) {
    for(int i = m_layers.size()-1; i >= 0; i--)
    {
        m_layers[i]->create(window.getSize().x, window.getSize().y);
    }
}

Renderer::Renderer(unsigned int width, unsigned int height) : window(sf::VideoMode(width,height), "LD 51") {
    color_map = std::make_shared<ColorMap>(window);
    window.setVerticalSyncEnabled(true);
    layers.add_layer(window);
    layers.add_layer(window);
    layers.add_layer(window);
}

void Renderer::begin_drawing() {
    window.clear();
    layers.clear_all_layers();
}

void Renderer::draw_object_on_layer(const sf::Drawable &object, int id_layer) {
    layers.get_layer(id_layer)->draw(object);
}

void Renderer::draw_object_on_layer(const sf::Drawable &object, int id_layer, const sf::RenderStates& opt_render_states) {
    layers.get_layer(id_layer)->draw(object,opt_render_states);
}


void Renderer::finish_drawing() {
    layers.draw_all_layers(window);
    #ifdef DEBUG_COLORS
        window.draw(sf::Sprite(color_map->color_texture.getTexture()));
        window.draw(sf::Sprite(color_map->dummy_texture.getTexture()));
    #endif
    window.display();
}

void Renderer::resize(unsigned int width, unsigned int height) {
    window.setSize({width, height});
    layers.resize_all_layers(window);
    color_map->resize_texture(window);
}

bool Renderer::is_open() {
    return window.isOpen();
}

bool Renderer::poll_event(sf::Event &event) {
    return window.pollEvent(event);
}

void Renderer::close() {
    window.close();
}


