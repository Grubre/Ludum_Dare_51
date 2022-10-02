#include "Enemy.hpp"

Enemy::Enemy(std::string name,
        float idleAnimationTime,
        float runingAnimationTime,
        float dyingAnimationTime,
        float hitAnimationTime,
        std::string _hurtSound,
        std::string _dyingSound,
        float _speed,
        int _health, float _stopTime)
    : MovingNode(name, idleAnimationTime, _speed)
    , health(_health)
    , hurtSound(_hurtSound)
    , dyingSound(_dyingSound), stopTime(_stopTime)
{
    HasBeenHit = false;
    animationManager.addAnimation("run", runingAnimationTime);
    animationManager.addAnimation("dying", dyingAnimationTime);
    animationManager.addAnimation("hit", hitAnimationTime);
    animationManager.addAnimation("dead", 100);
    isMoving = true;
    soundSystem = SoundSystem::getInstance();
}

Enemy::Enemy(EnemyPrototype p)
    : Enemy(p.name,
            p.idleAnimationTime,
            p.runingAnimationTime,
            p.dyingAnimationTime,
            p.hitAnimationTime,
            p._hurtSound,
            p._dyingSound,
            p._speed,
            p._health,
            p._stopTime)
{
}

void Enemy::setPosition(sf::Vector2f newPosition)
{
    body.setPosition(newPosition);
}

void Enemy::stopMoving()
{
    isMoving = false;
    if (health > 0) {
        animationManager.play("idle");
    }
}

void Enemy::startMoving() 
{ 
    isMoving = true; 
}

void Enemy::takeDamage(int dmg)
{
    if (health > 0) {
        health -= dmg;
        if (health <= 0) {
            animationManager.playOnce("dying");
            animationManager.setDefault("dead");
            soundSystem->playSound(dyingSound);
        } else {
            HasBeenHit = true;
            currentTime = 0.0;
            animationManager.playOnce("hit");
            soundSystem->playSound(hurtSound);
        }
    }
}

void Enemy::onUpdate(const sf::Time& delta)
{
    if (health > 0 && isMoving) {
        if (HasBeenHit) {
            currentTime += delta.asSeconds();
            if (currentTime >= stopTime) {
                HasBeenHit = false;
            }
        } else {
            sf::Vector2f newPosition = NewPositionByWaypoints(delta);
            if (newPosition.x > body.getPosition().x) {
                isFacingRight = true;
            } else if (newPosition.x < body.getPosition().x) {
                isFacingRight = false;
            }
            if (newPosition.x - body.getPosition().x != 0.0 ||
                newPosition.y - body.getPosition().y != 0.0) {
                animationManager.play("run");
            } else {
                animationManager.play("idle");
            }
            body.setPosition(newPosition);
        }
    }

    animationManager.update(delta, isFacingRight);
    body.setTexture(animationManager.getTexture().get());
    body.setTextureRect(animationManager.getIntRect());
}
