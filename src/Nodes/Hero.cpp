#include "Nodes/Hero.hpp"

Hero::Hero(std::string name, float idleAnimationTime, float _speed) : MovingNode(name, idleAnimationTime, _speed)
{

}

void Hero::loadWeapon(std::string name, float distance, sf::Vector2f center)
{
    weapon = create<Weapon>(shared_from_this(), name , distance, center);
}
