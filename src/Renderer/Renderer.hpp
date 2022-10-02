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
        Renderer(unsigned int width, unsigned int height);
        void begin_drawing();
        void draw_object_on_layer(const sf::Drawable &object, int id_layer);
        void draw_object_on_layer(const sf::Drawable &object, int id_layer, const sf::RenderStates& opt_render_states);
        void finish_drawing();
        bool is_open();
        bool poll_event(sf::Event &event);
        void close();
};
