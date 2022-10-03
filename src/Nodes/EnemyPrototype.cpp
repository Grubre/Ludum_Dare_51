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
    {"Orc5", {"Orc5", 0.5, 0.75, 0.5, 0.3, "hitHurt.wav", "explosion.wav", 100.0, 800, 0}},
    {"Undead1", {"Undead1", 0.5, 0.5, 0.5, 0.3, "hitHurt.wav", "explosion.wav", 350.0, 260, 0.3}},
    {"Undead2", {"Undead2", 0.5, 0.5, 0.5, 0.3, "hitHurt.wav", "explosion.wav", 200.0, 400, 0.3}},
    {"Undead3", {"Undead3", 0.5, 0.5, 0.5, 0.3, "hitHurt.wav", "explosion.wav", 200.0, 600, 0.1}},
    {"Undead4", {"Undead4", 0.5, 0.5, 0.5, 0.3, "hitHurt.wav", "explosion.wav", 250.0, 800, 0.1}},
    {"Undead5", {"Undead5", 0.5, 0.75, 0.5, 0.3, "hitHurt.wav", "explosion.wav", 100.0, 1600, 0}},
    {"Demon1", {"Demon1", 0.5, 0.5, 0.5, 0.3, "hitHurt.wav", "explosion.wav", 400.0, 360, 0.3}},
    {"Demon2", {"Demon2", 0.5, 0.5, 0.5, 0.3, "hitHurt.wav", "explosion.wav", 200.0, 600, 0.3}},
    {"Demon3", {"Demon3", 0.5, 0.5, 0.5, 0.3, "hitHurt.wav", "explosion.wav", 200.0, 900, 0.1}},
    {"Demon4", {"Demon4", 0.5, 0.5, 0.5, 0.3, "hitHurt.wav", "explosion.wav", 250.0, 1200, 0.1}},
    {"Demon5", {"Demon5", 0.5, 0.75, 0.5, 0.3, "hitHurt.wav", "explosion.wav", 100.0, 2400, 0}},
};