#pragma once

#include "Hero.hpp"

class Archer : public Hero
{
public:
    Archer(std::string name, float idleAnimationTime, float _speed);

protected:
    float attackSpeed;
    int damage;

private:
    void onUpdate(const sf::Time& delta) override;
};
