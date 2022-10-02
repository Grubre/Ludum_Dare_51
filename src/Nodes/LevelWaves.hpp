#pragma once 
#include "Wave.hpp"
#include "EnemyPrototype.hpp"
#include <map>
#include <string>
#include <fstream>

class LevelWaves : public Node
{
public:
    LevelWaves(std::string _levelName);
    

    static void setDirectory(std::string _directory);

    void nextWave();

    bool isThereNextWave();

    bool isWaveOn();

    void stopWaves();

private:
    std::string levelName;
    bool isInfoLoaded;
    std::map<int, std::vector<std::shared_ptr<Wave>>> waves;
    int index;
    float currentTime;
    static std::string directory;

    void onUpdate(const sf::Time& delta) override;
    void loadInfo();
};
