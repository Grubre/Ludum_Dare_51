 #include "LevelWaves.hpp" 

std::string LevelWaves::directory = "";

void LevelWaves::loadInfo()
{
    std::ifstream level(directory + levelName);

    char command;
    int activeWave = 0;
      
    while(level >> command)
    {
        switch (command)
        {
            case 'w':
            {
                level >> activeWave;
                waves[activeWave].push_back(create<Wave>(shared_from_this(), ysort));
            }
            break;
            
            case 'r':
            {
                float x, y;
                level >> x >> y;
                waves[activeWave].back()->addWaypoint({x,y});
            }
            break;

            case 'e':
            {
                std::string enemyName;
                int amount;
                level >> enemyName >> amount;
                waves[activeWave].back()->addEnemy(enemyName, amount);
            }
            break;

            default:
            break;
        }
    }
    
    isInfoLoaded = true;
}

void LevelWaves::setDirectory(std::string _directory)
{
    directory = _directory;
}

void LevelWaves::nextWave()
{
    if(isWaveOn())
        return;
    index++;
    for(long unsigned int i = 0; i < index; i++)
    {
        for(std::shared_ptr<Wave> w : waves[i])
        {
            w->TurnOnWave();
        }
    }
    currentTime = 0;
}

bool LevelWaves::isThereNextWave()
{
    if(waves.size() > index)
    {
        return true;
    }
    return false;
}

bool LevelWaves::isWaveOn()
{
    if(currentTime <= 10)
    {
        return true;
    }
    return false;
}

void LevelWaves::stopWaves()
{
    for(long unsigned int i = 0; i < index; i++)
    {
        for(std::shared_ptr<Wave> w : waves[i])
        {
            w->TurnOffWave();
        }
    }
}

void LevelWaves::onUpdate(const sf::Time& delta)
{
    if(!isInfoLoaded)
    {
        loadInfo();
    }

    if(currentTime > 10)
    {
        stopWaves();
    }
    else
    {
        currentTime += delta.asSeconds();
    }
}
