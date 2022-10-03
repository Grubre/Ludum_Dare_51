#pragma once
#include <iostream>
#include <optional>
#include "Standard/math.hpp"
#include <SFML/Graphics.hpp>

class ColorMap {
    public:
        explicit ColorMap(sf::RenderWindow& window) {
            color_texture.create(window.getSize().x, window.getSize().y);
            if(!color_id_shader.loadFromFile("assets/Shaders/color_id_shader.vert","assets/Shaders/color_id_shader.frag"))
                std::cerr << "Failed to load shaders in ColorMap!\n";
            color_id_shader.setUniform("texture", sf::Shader::CurrentTexture);
        }

        void resize_texture(sf::RenderWindow& window) {
            color_texture.create(window.getSize().x, window.getSize().y);
        }

        void draw_object(const sf::Drawable& object) {
            color_texture.draw(object, &color_id_shader);
        }

        void draw_object(const sf::Drawable& object, sf::RenderStates state) {
            state.shader = &color_id_shader;
            color_texture.draw(object, state);
        }

        std::optional<sf::Color> get_color_at(engine::Vec2i at) {
            auto position = sf::Vector2i(at);
            auto image = color_texture.getTexture().copyToImage();
            if(!((position.x < 0 || (unsigned int)position.x >= image.getSize().x) || (position.y < 0 || (unsigned int)position.y >= image.getSize().y)) )
            {
                auto color = image.getPixel(position.x,position.y);
                if(color.r != 0 || color.g != 0 || color.b != 0 || color.a != 0) {
                    return std::optional<sf::Color>(color);
                }
            }
            return {};
        }

        std::optional<sf::Color> get_color_at_world(engine::Vec2f at) {
            return get_color_at(engine::Vec2i(color_texture.mapCoordsToPixel(sf::Vector2f(at))));
        }

        sf::Shader color_id_shader;
        sf::RenderTexture color_texture;
    private: 
};
