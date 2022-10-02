#pragma once 
#include "Wave.hpp"
#include "EnemyPrototype.hpp"
#include <map>
#include <string>
#include <fstream>

class LevelWaves : public Node
{
public:
    LevelWaves(std::shared_ptr<YSort> _ysort,std::string _levelName) : ysort(_ysort), levelName(_levelName)
    {
        isInfoLoaded = false;
        currentTime = 20;
        index = 0;
        if(directory == "")
        {
            std::cout << "Levelwaves directory not set, use LevelWaves::setDirectory(\"\")" << std::endl;
        }
    }
    
    static void setDirectory(std::string _directory);

    void nextWave();

    bool isThereNextWave();

    bool isWaveOn();

    void stopWaves();

private:
    std::shared_ptr<YSort> ysort;
    std::string levelName;
    bool isInfoLoaded;
    std::map<int, std::vector<std::shared_ptr<Wave>>> waves;
    long unsigned int index;
    float currentTime;
    static std::string directory;

    void onUpdate(const sf::Time& delta) override;
    void loadInfo();
};
