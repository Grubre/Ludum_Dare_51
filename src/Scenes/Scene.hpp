#pragma once
#include "Nodes/Node.hpp"

class Scene : public Node{
    protected:
    Renderer& renderer;
    Scene** curr_scene_ptr;
    public:
        Scene(Renderer& renderer, Scene** curr_scene_ptr)
            : renderer(renderer), curr_scene_ptr(curr_scene_ptr)
        {}
    virtual void draw(){};
    virtual void update([[maybe_unused]]const sf::Time& delta){};
};
