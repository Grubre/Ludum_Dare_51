#include <filesystem>
#include <assert.h>

#include "AnimationLoaderPrototypeFactory.hpp"

AnimationLoaderPrototypeFactory* AnimationLoaderPrototypeFactory::instance = nullptr;

std::shared_ptr<AnimationLoader> AnimationLoaderPrototypeFactory::make(std::string name)
{
    if(!prototypes.count(name))
    {
        std::cerr << "There's no directory " << name << " in your textures directory  " << std::endl;
    }
    return prototypes[name];
}

AnimationLoaderPrototypeFactory* AnimationLoaderPrototypeFactory::getInstance(std::string directoryPath)
{
    if(instance == nullptr)
    {
        assert(directoryPath != "");
        instance = new AnimationLoaderPrototypeFactory(directoryPath);
    }

    return instance;
}

AnimationLoaderPrototypeFactory::AnimationLoaderPrototypeFactory(std::string directoryPath)
{
    for(const auto &entry: std::filesystem::directory_iterator(directoryPath))
    {
        AnimationLoader loader(entry.path().string());

        std::string name = entry.path().string();
        name.erase(0,directoryPath.length());

        prototypes[name] = std::make_shared<AnimationLoader>(loader);
    }
}
