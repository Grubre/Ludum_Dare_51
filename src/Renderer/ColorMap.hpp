#pragma once
#include <iostream>
#include <optional>
#include "Standard/math.hpp"
#include <SFML/Graphics.hpp>

class ColorMap {
    public:
        explicit ColorMap(sf::RenderWindow& window) {
            color_texture.create(window.getSize().x, window.getSize().y);
            dummy_texture.create(1,1);

            if(!color_id_shader.loadFromFile("assets/Shaders/color_id_shader.frag", sf::Shader::Fragment))
                std::cerr << "Failed to load shaders in ColorMap!\n";
            if(!dummy_shader.loadFromFile("assets/Shaders/dummy_shader.frag", sf::Shader::Fragment))
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
            if(!((at.x < 0 || (unsigned int)at.x >= color_texture.getSize().x) || (at.y < 0 || (unsigned int)at.y >= color_texture.getSize().y)) )
            {
                render_to_dummy_texture(at);
                auto image = dummy_texture.getTexture().copyToImage();

                auto color = image.getPixel(0,0);
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
        sf::RenderTexture dummy_texture;
        sf::Shader dummy_shader;

        void render_to_dummy_texture(engine::Vec2i at) {
            dummy_texture.clear();

            dummy_shader.setUniform("texture", color_texture.getTexture());
            dummy_shader.setUniform("mouse_pos", sf::Vector2f((float)at.x / color_texture.getSize().x, (float)at.y / color_texture.getSize().y));

            dummy_texture.draw(sf::Sprite(color_texture.getTexture()), &dummy_shader);

            dummy_texture.display();
        }

};
