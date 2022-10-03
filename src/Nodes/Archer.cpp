#include "Nodes/Archer.hpp"

Archer::Archer(float idleAnimationTime, float runAnimationTime, float _speed, sf::Vector2f _centerOfWeapon, float _attackSpeed) 
: Hero("Archer", idleAnimationTime, _speed, _centerOfWeapon, _attackSpeed)
{
    animationManager.addAnimation("run", runAnimationTime);
    isWeaponLoaded = false;
}

void Archer::onUpdate(const sf::Time& delta)
{
    if(!isWeaponLoaded)
    {
        isWeaponLoaded = true;
    }

    sf::Vector2f newTranslate = NewTranslateByWaypoints(delta);
    if (newTranslate.x > getGlobalTranslation().x) {
        isFacingRight = true;
    } else if (newTranslate.x < getGlobalTranslation().x) {
        isFacingRight = false;
    }
    if (newTranslate.x - getGlobalTranslation().x != 0.0 ||
        newTranslate.y - getGlobalTranslation().y != 0.0) {
        animationManager.play("run");
    } else {
        animationManager.play("idle");
    }
    setTranslation(newTranslate);

    engine::Vec2i mousePosition = engine::Vec2i{sf::Mouse::getPosition()}; //Change to better

    float Xdiff, Ydiff;

    Xdiff = mousePosition.x - getGlobalTranslation().x - centerOfWeapon.x;
    Ydiff = getGlobalTranslation().y + centerOfWeapon.y - mousePosition.y;

    if(Xdiff != 0 || Ydiff != 0)
    {
    }

    updateAttack(delta);

    animationManager.update(delta, isFacingRight);
    body.setTexture(animationManager.getTexture().get());
    body.setTextureRect(animationManager.getIntRect());
}

void Archer::doAttack()
{
    std::cout << "Archer is Attacking" << std::endl;
}
