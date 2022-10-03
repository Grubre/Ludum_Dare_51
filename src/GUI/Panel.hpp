#pragma once
#include "GUI/GUI.hpp"

template<std::size_t items_width>
class Panel : public GUI{
    std::size_t width, height;

public:
    Panel(std::size_t width, std::size_t height) : width(width), height(height) {}

protected:
    void onDraw([[maybe_unused]]Renderer &renderer) const override{

    }
     void onUpdate([[maybe_unused]] const sf::Time& delta) override{

    }
};
