#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Layers
{
  public:
    using layer_ptr = std::shared_ptr<sf::RenderTexture>;

    //Singleton Pattern    
    static Layers* get_instance();

    //Managing Layers
    void add_layer(const sf::RenderWindow& window, std::string name = "layer");
    layer_ptr get_layer(unsigned long id = 1) const;
    layer_ptr get_layer(const std::string& name) const;
    std::vector<layer_ptr>& get_layers();

    layer_ptr operator[](unsigned long id) const;
    layer_ptr operator[](const std::string &name) const;

    //Operations
    void clear_all_layers();
    void draw_all_layers(sf::RenderWindow& window);
    void resize_all_layers(const sf::RenderWindow& window);

  private:
    static Layers* m_instance;

    std::vector<layer_ptr> m_layers;
    std::unordered_map<std::string, layer_ptr> m_mappings;
};
