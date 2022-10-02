#pragma once
#include <string>
#include <map>

class EnemyPrototype
{
public:
    EnemyPrototype();

     EnemyPrototype(std::string _name, float _idleAnimationTime, float _runingAnimationTime, float _dyingAnimationTime, 
     float _hitAnimationTime, std::string __hurtSound, std::string __dyingSound, float __speed,int __health, float __stopTime);

    std::string name; 
    float idleAnimationTime;
    float runingAnimationTime; 
    float dyingAnimationTime; 
    float hitAnimationTime; 
    std::string _hurtSound; 
    std::string _dyingSound; 
    float _speed;
    int _health;
    float _stopTime;
};

extern std::map<std::string, EnemyPrototype> prototypes;