#pragma once
#include "MovingNode.hpp"
#include "Music/All.hpp"
#include "Nodes/EnemyPrototype.hpp"

class Enemy : public MovingNode
{
  public:
    Enemy(std::string name,
          float idleAnimationTime,
          float runingAnimationTime,
          float dyingAnimationTime,
          float hitAnimationTime,
          std::string _hurtSound,
          std::string _dyingSound,
          float _speed,
          int _health, float _stopTime);

    Enemy(EnemyPrototype p);

    void stopMoving();

    void startMoving();

    void takeDamage(int dmg);

  private:
    float currentTime;
    float stopTime;
    bool HasBeenHit;
    int health;
    bool isFacingRight;
    bool isMoving;
    SoundSystem* soundSystem;
    std::string hurtSound;
    std::string dyingSound;

    void onUpdate(const sf::Time& delta) override;
};
