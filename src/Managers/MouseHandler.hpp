#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer/ColorMap.hpp"
#include <memory>
#include "Standard/Math/Hashers.hpp"

class MouseSubscriber {
    public:
        virtual void render_to_color_map(ColorMap& color_map) = 0;
        virtual void handle_press(sf::Event &event) {};
        virtual void handle_move(sf::Event &event) {};
        virtual void handle_release(sf::Event &event) {};
};

class MouseHandler {
    public:

        static MouseHandler* get_instance();
        static void initialize(std::shared_ptr<ColorMap> color_map);

        void handle_press(sf::Event &event);
        void handle_move(sf::Event &event);
        void handle_release(sf::Event &event);

        void register_subscriber(std::weak_ptr<MouseSubscriber> subscriber);

    private:
        static MouseHandler* m_instance;

        explicit MouseHandler(std::shared_ptr<ColorMap> color_map);

        void render_colors();
        std::optional<std::shared_ptr<MouseSubscriber>> get_object_at_mouse_position(int x, int y);

        std::shared_ptr<ColorMap> color_map;

        std::unordered_map<sf::Color, std::weak_ptr<MouseSubscriber>> color_lookup;  
};
