#pragma once
#include "Enemy.hpp"
#include "EnemyPrototype.hpp"
#include <vector>
#include <string>

class Wave : public Node
{
public:
    Wave(sf::Vector2f start)
    {
        waypoints.push_back(start);
    }

    void addEnemy(std::string name, int amount)
    {
        enemiesNames.push_back(name);
        amountOfEnemies.push_back(amount);
        sumOfEnemies += amount;
        timeBetween = 10.0/sumOfEnemies;
        currentTime = timeBetween;
    }
    void addWaypoint(sf::Vector2f waypoint)
    {
        waypoints.push_back(waypoint);
    }

    void TurnOnWave()
    {
        isWaveOn = true;
        for(std::shared_ptr<Enemy> enemy : enemies)
        {
            enemy->startMoving();
        }
    }

    void TurnOffWave()
    {
        isWaveOn = false;
        for(std::shared_ptr<Enemy> enemy : enemies)
        {
            enemy->stopMoving();
        }
    }

private:
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

    void onUpdate(const sf::Time& delta) override
    {
        if(isWaveOn)
        {
            currentTime += delta.asSeconds();
            while(currentTime > timeBetween && indexofEnemy < enemiesNames.size())
            {
                currentTime -= timeBetween;
                enemies.push_back(create<Enemy>(shared_from_this(), prototypes[enemiesNames[indexofEnemy]]));
                enemies.back()->setPosition(waypoints[0]);
                enemies.back()->setScale(5);
                for(sf::Vector2f waypoint : waypoints)
                {
                    enemies.back()->addNewWaypoint(waypoint);
                }

                countOfEnemies++;
                if(countOfEnemies >= amountOfEnemies[indexofEnemy])
                {
                    indexofEnemy++;
                    countOfEnemies = 0;
                }
            }
        }
    }
};
