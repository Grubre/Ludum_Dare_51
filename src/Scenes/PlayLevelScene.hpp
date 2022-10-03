#pragma once

#include "Scenes/Scene.hpp"
#include "Nodes/Archer.hpp"
#include "GUI/Text.hpp"
#include "Nodes/SortNode.hpp"
#include "Nodes/LevelWaves.hpp"
#include "Managers/KeymapManager.hpp"

class PlayLevelScene : public Scene{
    std::shared_ptr<Text> text;

    std::shared_ptr<YSort> ysort;
    std::shared_ptr<LevelWaves> test;

    std::shared_ptr<Archer> e1Test;

    public:
    PlayLevelScene(Renderer& renderer, Scene** curr_scene_ptr) : Scene(renderer, curr_scene_ptr),
        text(Text::create<Text>(ResourceLoader::get_instance()->load_font("arial.ttf") , "Main Menu")),
        ysort(YSort::create<YSort>()),
        test(LevelWaves::create<LevelWaves>(ysort, "level1.lvl")),
        e1Test(Archer::create<Archer>(ysort, 0.5, 0.5, 200, sf::Vector2f(0, -10), 0.5))
    {
        text->text().setString("Play Level");
        KeymapManager::get_instance()->register_keymap(sf::Keyboard::Num1, [this](){
            test->nextWave();
            text->text().setString("Wave incoming!");
        });
    }

    void draw() override {
        text->draw(renderer);
        test->draw(renderer);
        ysort->draw(renderer);
    }
    void update([[maybe_unused]]const sf::Time &delta) override {
        test->update(delta);
        text->update(delta);
        ysort->update(delta);
    }
};
