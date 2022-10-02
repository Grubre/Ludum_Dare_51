#pragma once
#include "AnimationLoader.hpp"

class AnimationLoaderPrototypeFactory
{
public:
    std::shared_ptr<AnimationLoader> make(std::string name);
    static AnimationLoaderPrototypeFactory* getInstance(std::string directoryPath = "");

private:
    AnimationLoaderPrototypeFactory(std::string directoryPath);
    std::map<std::string, std::shared_ptr<AnimationLoader>> prototypes;

    static AnimationLoaderPrototypeFactory* instance;
};
