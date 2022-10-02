#pragma once
#include <string>

class EnemyPrototype
{
public:
    EnemyPrototype()
    {
        
    }
     EnemyPrototype(std::string _name, float _idleAnimationTime, float _runingAnimationTime, float _dyingAnimationTime, 
     float _hitAnimationTime, std::string __hurtSound, std::string __dyingSound, float __speed,int __health)
     : name(_name), idleAnimationTime(_idleAnimationTime), runingAnimationTime(_runingAnimationTime), 
     dyingAnimationTime(_dyingAnimationTime), hitAnimationTime(_hitAnimationTime), _hurtSound(__hurtSound), 
     _dyingSound(__dyingSound),_speed(__speed),_health(__health)  
     {}

    std::string name; 
    float idleAnimationTime;
    float runingAnimationTime; 
    float dyingAnimationTime; 
    float hitAnimationTime; 
    std::string _hurtSound; 
    std::string _dyingSound; 
    float _speed;
    int _health;
};

std::map<std::string, EnemyPrototype> prototypes= 
{
    {"Orc1", {"Orc1", 0.5, 0.5, 0.5, 0.5, "hitHurt.wav", "explosion.wav", 300.0, 120}}
};