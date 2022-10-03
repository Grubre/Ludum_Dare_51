#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer/ColorMap.hpp"
#include <memory>

class MouseHandler {
    public:

        static MouseHandler* get_instance();
        static void initialize(std::shared_ptr<ColorMap> color_map);

        void handle_press(sf::Event &event);
        void handle_move(sf::Event &event);
        void handle_release(sf::Event &event);

        auto get_pointed_object(){
            return color_map->get_color_at(engine::Vec2i{sf::Mouse::getPosition()});
        }

    private:
        static MouseHandler* m_instance;

        explicit MouseHandler(std::shared_ptr<ColorMap> color_map);

        std::shared_ptr<ColorMap> color_map;

        std::vector<std::weak_ptr<ColorRenderable>> subscribed_objects;  
};
