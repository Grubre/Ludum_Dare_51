#pragma once
#include <SFML/Graphics.hpp>
#include "Standard/math.hpp"
#include <memory>
#include <optional>

class ColorIDMap
{
  public:
    using layer_ptr = std::shared_ptr<sf::RenderTexture>;

    static ColorIDMap* get_instance();
    sf::Color generate_unique_color_id();

    layer_ptr get_color_layer();

    std::optional<sf::Color> get_color_at(engine::Vec2i at);
    std::optional<sf::Color> get_color_at_world(engine::Vec2f at);

    static sf::Shader* color_id_shader;

  private:
    static ColorIDMap* m_instance;

    layer_ptr m_color_layer;
    int curr_node_id = 2215;

    ColorIDMap()
    {
        m_color_layer = std::make_shared<sf::RenderTexture>();
        m_color_layer->create(1600, 900);
    }
};