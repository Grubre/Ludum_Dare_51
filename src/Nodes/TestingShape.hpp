#pragma once
#include "Node.hpp"
#include "Managers/MouseHandler.hpp"
#include <iostream>

class TestingShape : public Node, public MouseSubscriber
{
    sf::CircleShape shape = sf::CircleShape(40.f);

    void onDraw(Renderer &renderer) const override { renderer.draw_object_on_layer(shape,0, global_transform.getTransform()); }

    void render_to_color_map(ColorMap& color_map) override {
      color_map.draw_object(shape, global_transform.getTransform());
    }

    void handle_press(sf::Event &event) {
      std::cout<< "Test " << event.mouseButton.x << " " << event.mouseButton.y << std::endl;
    }

    public:
      TestingShape() { }
};
