#pragma once
#include "Enemy.hpp"
#include "Wave.hpp"
#include <fstream>

static std::string directory = "directory not set, use EnemyWavesManager::setDirectory(\"\")";

class EnemyWavesManager : public Node
{
public:
    EnemyWavesManager(std::string levelName)
    {
        if(directory == "directory not set, use EnemyWavesManager::setDirectory(\"\")")
        {
            std::cout << directory << std::endl;
        }
        currentTime = 0.0f;
        std::ifstream level(directory + levelName);

        char commandType;

        while(level >> commandType)
        {
            switch (commandType)
            {
                case 'r':
                {
                    float x, y;
                    level >> x >> y;
                    waypoints.push_back({x,y});
                }
                break;

                case 'w':
                {
                    level >> index;
                }
                break;

                case 'e':
                {
                    std::string enemyName;
                    float timesBetween;
                    int amountOfEnemies;
                    level >> enemyName >> timesBetween >> amountOfEnemies;
                    waves[index].enemiesNames.push_back(enemyName);
                    waves[index].timesBetween.push_back(timesBetween);
                    waves[index].amountOfEnemies.push_back(amountOfEnemies);
                }
                break;
            
                default:
                    std::cout << "Błąd syntaxu w " << levelName << std::endl;
                break;
            };
        }
        index = 1;
        AmountOfWaves = waves.size();
    }

    static void setDirectory(std::string _directory)
    {
        directory = _directory;
    }
    
private:
    static std::string directory;
    float currentTime;
    int index;
    int AmountOfWaves;
    std::map<int, Wave> waves;
    std::vector<sf::Vector2f> waypoints;
    void onUpdate(const sf::Time& delta) override
    {
        
    }
};
