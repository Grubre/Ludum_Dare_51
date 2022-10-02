#include "Wave.hpp"

void Wave::addEnemy(std::string name, int amount)
{
    enemiesNames.push_back(name);
    amountOfEnemies.push_back(amount);
    sumOfEnemies += amount;
    timeBetween = 10.0/sumOfEnemies;
    currentTime = timeBetween;
}

void Wave::addWaypoint(sf::Vector2f waypoint)
{
    waypoints.push_back(waypoint);
}

void Wave::TurnOnWave()
{
    isWaveOn = true;
    for(std::shared_ptr<Enemy> enemy : enemies)
    {
        enemy->startMoving();
    }
}

void Wave::TurnOffWave()
{
    isWaveOn = false;
    for(std::shared_ptr<Enemy> enemy : enemies)
    {
        enemy->stopMoving();
    }
}

void Wave::onUpdate(const sf::Time& delta)
{
    if(isWaveOn)
    {
        currentTime += delta.asSeconds();
        while(currentTime > timeBetween && indexofEnemy < enemiesNames.size())
        {
            currentTime -= timeBetween;
            enemies.push_back(create<Enemy>(ysort, prototypes[enemiesNames[indexofEnemy]]));
            enemies.back()->setTranslation(waypoints[0]);
            enemies.back()->setScale(4);
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
