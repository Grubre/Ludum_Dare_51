#include "Nodes/Archer.hpp"

Archer::Archer(std::string name, float idleAnimationTime, float _speed) : Hero(name, idleAnimationTime, _speed)
{
    loadWeapon("Bow", 10, {0.0, -10.0});
}

void Archer::onUpdate(const sf::Time& delta)
{

}
