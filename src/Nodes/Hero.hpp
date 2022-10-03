#pragma once
#include "MovingNode.hpp"
#include "Weapon.hpp"

class Hero : public MovingNode
{
public:
    Hero(std::string name, float idleAnimationTime, float _speed);

protected:
    std::shared_ptr<Weapon> weapon;
    void loadWeapon(std::string name, float distance, sf::Vector2f center);
};
