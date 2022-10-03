#include "Nodes/Hero.hpp"

Hero::Hero(std::string name, float idleAnimationTime, float _speed, sf::Vector2f _centerOfWeapon, float _attackSpeed) 
: MovingNode(name, idleAnimationTime, _speed), centerOfWeapon(_centerOfWeapon), attackSpeed(_attackSpeed)
{
    currentTime = 0.0;
}

void Hero::loadWeapon(std::string name, float distance)
{
    weapon = create<Weapon>(shared_from_this(), name , distance, centerOfWeapon);
}

void Hero::updateAttack(const sf::Time& delta)
{
    currentTime += delta.asSeconds();
    while(currentTime >= attackSpeed)
    {
        currentTime -= attackSpeed;
        doAttack();
    }
}

void Hero::doAttack()
{

}
