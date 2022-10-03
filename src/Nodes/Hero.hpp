#pragma once
#include "MovingNode.hpp"

class Hero : public MovingNode
{
public:
    Hero(std::string name, float idleAnimationTime, float _speed, sf::Vector2f _centerOfWeapon, float _attackSpeed);

protected:
    float currentTime;
    float attackSpeed;
    sf::Vector2f centerOfWeapon;
    void loadWeapon(float distance);
    void updateAttack(const sf::Time& delta);
    virtual void doAttack();
};
