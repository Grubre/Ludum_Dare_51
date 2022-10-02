#pragma once
#include "Node.hpp"
#include "Animation/All.hpp"
#include <queue>
#include <math.h>

class MovingNode : public Node
{
public:
    MovingNode(std::string name, float idleAnimationTime, float _speed);

    void setScale(float scale);

    void addNewWaypoint(sf::Vector2f n);

protected:
    AnimationManager animationManager;
    sf::RectangleShape body;
    float speed;
    sf::Vector2f NewPositionByWaypoints(const sf::Time& delta);

private:
    std::queue<sf::Vector2f> waypoints;

    void onUpdate(const sf::Time& delta) override;

    void onDraw(Renderer &renderer) const override;
};
