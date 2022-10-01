#include "Node.hpp"

class TestingShape : public Node
{
    sf::CircleShape shape = sf::CircleShape(40.f);

    void onDraw(Renderer &renderer) const override { renderer.draw_object_on_layer(shape,0); }

  public:
    TestingShape() { }
};
