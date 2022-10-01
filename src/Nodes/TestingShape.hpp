#include "Node.hpp"

class TestingShape : public Node
{
    sf::CircleShape shape = sf::CircleShape(40.f);

    void onDraw() const override { render_layer->draw(shape); }

  public:
    TestingShape() { render_layer = Layers::get_instance()->get_layer(0); }
};