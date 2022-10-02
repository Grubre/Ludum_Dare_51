#include "EnemyPrototype.hpp"
EnemyPrototype::EnemyPrototype()
{}

EnemyPrototype::EnemyPrototype(std::string _name, float _idleAnimationTime, float _runingAnimationTime, float _dyingAnimationTime, 
float _hitAnimationTime, std::string __hurtSound, std::string __dyingSound, float __speed,int __health, float __stopTime)
: name(_name), idleAnimationTime(_idleAnimationTime), runingAnimationTime(_runingAnimationTime), 
dyingAnimationTime(_dyingAnimationTime), hitAnimationTime(_hitAnimationTime), _hurtSound(__hurtSound), 
_dyingSound(__dyingSound),_speed(__speed),_health(__health), _stopTime(__stopTime)  
{}

std::map<std::string, EnemyPrototype> prototypes= 
{
    {"Orc1", {"Orc1", 0.5, 0.5, 0.5, 0.3, "hitHurt.wav", "explosion.wav", 300.0, 120, 0.3}},
    {"Orc2", {"Orc2", 0.5, 0.5, 0.5, 0.3, "hitHurt.wav", "explosion.wav", 200.0, 200, 0.3}},
    {"Orc3", {"Orc3", 0.5, 0.5, 0.5, 0.3, "hitHurt.wav", "explosion.wav", 200.0, 300, 0.1}},
    {"Orc4", {"Orc4", 0.5, 0.5, 0.5, 0.3, "hitHurt.wav", "explosion.wav", 250.0, 400, 0.1}},
    {"Orc5", {"Orc5", 0.5, 0.75, 0.5, 0.3, "hitHurt.wav", "explosion.wav", 70.0, 800, 0}}
};