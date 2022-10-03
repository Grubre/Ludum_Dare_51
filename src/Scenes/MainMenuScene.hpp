#pragma once
#include "Nodes/LevelWaves.hpp"
#include "Nodes/SortNode.hpp"
#include "Scenes/Scene.hpp"
#include "GUI/Text.hpp"
#include "Managers/KeymapManager.hpp"

class MainMenuScene : public Scene{
    Renderer& renderer;
    Scene** curr_scene_ptr;
    std::shared_ptr<Text> text;

    std::shared_ptr<YSort> ysort;
    std::shared_ptr<LevelWaves> test;
public:
    MainMenuScene(Renderer& renderer, Scene** curr_scene_ptr) :
        renderer(renderer), curr_scene_ptr(curr_scene_ptr),
        text(Text::create<Text>(ResourceLoader::get_instance()->load_font("arial.ttf") , "Main Menu")),
        ysort(YSort::create<YSort>()),
        test(LevelWaves::create<LevelWaves>(ysort, "level1.lvl"))
    {
        KeymapManager::get_instance()->register_keymap(sf::Keyboard::Num1, [this](){
            test->nextWave();
            text->text().setString("Wave incoming!");
        });
    }
    virtual void draw() {
        text->draw(renderer);
        test->draw(renderer);
        ysort->draw(renderer);
    }
    virtual void update([[maybe_unused]]const sf::Time& delta) {
        test->update(delta);
        text->update(delta);
        ysort->update(delta);
    }
};
