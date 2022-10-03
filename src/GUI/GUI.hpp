#pragma once
#include "Nodes/Node.hpp"

class GUI : public Node{
    virtual void onDraw([[maybe_unused]]Renderer &renderer) const override{}
    virtual void onUpdate([[maybe_unused]] const sf::Time& delta) override{}
};
