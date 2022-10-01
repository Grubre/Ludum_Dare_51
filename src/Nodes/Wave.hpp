#pragma once
#include "Enemy.hpp"
#include <vector>
#include <string>

class Wave : public Node
{
public:
    Wave()
    {

    }

    void addEnemy(std::string name, int amount)
    {
        enemiesNames.push_back(name);
        amountOfEnemies.push_back(amount);
        sumOfEnemies += amount;
        timeBetween = 10.0/sumOfEnemies;
        currentTime = timeBetween;
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

    void onUpdate(const sf::Time& delta) override
    {
        if(isWaveOn)
        {
            currentTime += delta.asSeconds();
            while(currentTime > timeBetween && indexofEnemy < enemiesNames.size())
            {
                currentTime -= timeBetween;
                children.push_back(Enemy::create<Enemy>("Orc1", 0.5, 0.5, 0.5, 0.5, "hitHurt.wav", "explosion.wav", 700, 120));
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
