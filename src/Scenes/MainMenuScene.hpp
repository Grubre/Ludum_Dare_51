#pragma once
#include "Nodes/LevelWaves.hpp"
#include "Nodes/SortNode.hpp"
#include "Scenes/Scene.hpp"
#include "Scenes/PlayLevelScene.hpp"
#include "GUI/Text.hpp"
#include "Managers/KeymapManager.hpp"
#include "Nodes/Archer.hpp"

class MainMenuScene : public Scene{
    Scene* playLevelScene;
 
    public:
    MainMenuScene(Renderer& renderer, Scene** curr_scene_ptr) :
        Scene(renderer, curr_scene_ptr),
        playLevelScene(new PlayLevelScene(renderer,curr_scene_ptr))
    {
        KeymapManager::get_instance()->register_keymap(sf::Keyboard::Space, [this](){
            *this->curr_scene_ptr = playLevelScene;
        });
    }
    virtual void draw() {
            }
    virtual void update([[maybe_unused]]const sf::Time& delta) {
            }
};
