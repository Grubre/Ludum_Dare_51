#pragma once
#include <SFML/Graphics.hpp>

class Renderer {

    using Layer = sf::RenderTexture;

    class Layers
    {
        public:  
            //Managing Layers
            void add_layer(const sf::RenderWindow& window);
            Layer* get_layer(unsigned long id);
            Layer* operator[](unsigned long id);

            //Operations
            void clear_all_layers();
            void draw_all_layers(sf::RenderWindow& window);
            void resize_all_layers(const sf::RenderWindow& window);

        private:
            std::vector<Layer*> m_layers;
    };

    sf::RenderWindow window;
    Layers layers;

    public:
        Renderer(unsigned int width, unsigned int height) : window(sf::VideoMode(width,height), "LD 51") {
            window.setVerticalSyncEnabled(true);
            layers.add_layer(window);
            layers.add_layer(window);
            layers.add_layer(window);
        }

        void begin_drawing() {
            window.clear();
            layers.clear_all_layers();
        }

        void draw_object_on_layer(const sf::Drawable &object, int id_layer) {
            layers.get_layer(id_layer)->draw(object);
        };

        void finish_drawing() {
            layers.draw_all_layers(window);
            window.display();
        }

        bool is_open() {
            return window.isOpen();
        }

        bool poll_event(sf::Event &event) {
            return window.pollEvent(event);
        }

        void close() {
            window.close();
        }

};
