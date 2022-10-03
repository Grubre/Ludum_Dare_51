#pragma once

#include "Node.hpp"
#include "Animation/AnimationManager.hpp"

class Weapon : public Node
{
public:
    Weapon(std::string name, float _distance, sf::Vector2f center = {0.0, 0.0});
    float angle;

protected:
    sf::RectangleShape body;
    float distance;
    AnimationManager animationManager;

    sf::Vector2f center;

    sf::Vector2f NewTranslateByAngle(float angle);

    void onUpdate(const sf::Time& delta) override;

    void onDraw(Renderer &renderer) const override;
};
