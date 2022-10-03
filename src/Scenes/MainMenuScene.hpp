#pragma once
#include "Nodes/LevelWaves.hpp"
#include "Nodes/SortNode.hpp"
#include "Scenes/Scene.hpp"
#include "GUI/Text.hpp"
#include "Managers/KeymapManager.hpp"
#include "Nodes/Archer.hpp"

class MainMenuScene : public Scene{
    Renderer& renderer;
    Scene** curr_scene_ptr;
    std::shared_ptr<Text> text;

    std::shared_ptr<YSort> ysort;
    std::shared_ptr<LevelWaves> test;

    std::shared_ptr<Archer> e1Test;
public:
    MainMenuScene(Renderer& renderer, Scene** curr_scene_ptr) :
        renderer(renderer), curr_scene_ptr(curr_scene_ptr),
        text(Text::create<Text>(ResourceLoader::get_instance()->load_font("arial.ttf") , "Main Menu")),
        ysort(YSort::create<YSort>()),
        test(LevelWaves::create<LevelWaves>(ysort, "level1.lvl")),
        e1Test(Archer::create<Archer>(ysort, 0.5, 0.5, 200, sf::Vector2f(0, -10), 0.5))
    {
        e1Test->setTranslation({100, 100});
        e1Test->addNewWaypoint({500, 100});
        e1Test->addNewWaypoint({500, 400});
        e1Test->addNewWaypoint({500, 700});
        e1Test->addNewWaypoint({700, 700});
        e1Test->setScale(4);
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
