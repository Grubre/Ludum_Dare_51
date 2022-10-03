#pragma once
#include "Node.hpp"
#include "Managers/MouseHandler.hpp"
#include <iostream>

class TestingShape : public Node, public MouseSubscriber
{
    sf::CircleShape shape = sf::CircleShape(40.f);

    bool mouse_pressed = false;
    engine::Vec2f rel_clicked_spot;

    void onDraw(Renderer &renderer) const override { renderer.draw_object_on_layer(shape,0, global_transform.getTransform()); }

    void render_to_color_map(ColorMap& color_map) override {
      color_map.draw_object(shape, global_transform.getTransform());
    }

    void handle_press(sf::Event &event) override {
      mouse_pressed = true;
      rel_clicked_spot = {getGlobalTranslation().x - event.mouseButton.x, getGlobalTranslation().y - event.mouseButton.y};
      std::cout<< "Test " << event.mouseButton.x << " " << event.mouseButton.y << std::endl;
    }

    void handle_move(sf::Event &event) override {
      if(mouse_pressed){
        setGlobalTranslation(sf::Vector2f(engine::Vec2f{event.mouseMove.x, event.mouseMove.y} + rel_clicked_spot));
      }
    }

    void handle_release(sf::Event &event) override {
      mouse_pressed = false;
    }

    public:
      TestingShape() { }
};
