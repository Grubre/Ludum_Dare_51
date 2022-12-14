#pragma once
#include "Enemy.hpp"
#include "EnemyPrototype.hpp"
#include "SortNode.hpp"
#include <vector>
#include <string>

class Wave : public Node
{
public:
    
    Wave(std::shared_ptr<YSort> _ysort) : ysort(_ysort)
    {}
    void addEnemy(std::string name, int amount);
    void addWaypoint(sf::Vector2f waypoint);

    void TurnOnWave();

    void TurnOffWave();

private:
    std::shared_ptr<YSort> ysort;
    bool isWaveOn = false;
    std::vector<std::string> enemiesNames;
    float timeBetween;
    std::vector<int> amountOfEnemies;
    int sumOfEnemies = 0;
    float currentTime;
    int indexofEnemy = 0;
    int countOfEnemies = 0;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<sf::Vector2f> waypoints;

    void onUpdate(const sf::Time& delta) override;
};
