#pragma once

#include "Hero.hpp"

class Archer : public Hero
{
public:
    Archer(float idleAnimationTime, float runAnimationTime, float _speed, sf::Vector2f _centerOfWeapon, float _attackSpeed);

private:
    bool isWeaponLoaded;
    void onUpdate(const sf::Time& delta) override;
    void doAttack() override;
};
