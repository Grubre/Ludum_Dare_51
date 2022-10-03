#pragma once
#include "Nodes/LevelWaves.hpp"
#include "Nodes/SortNode.hpp"
#include "Scenes/Scene.hpp"
#include "GUI/Text.hpp"
#include "Managers/KeymapManager.hpp"
#include "Nodes/Weapon.hpp"

class MainMenuScene : public Scene{
    Renderer& renderer;
    Scene** curr_scene_ptr;
    std::shared_ptr<Text> text;

    std::shared_ptr<YSort> ysort;
    std::shared_ptr<LevelWaves> test;

    std::shared_ptr<Enemy> e1Test;
    std::shared_ptr<Weapon> w1Test;

    std::shared_ptr<Enemy> e2Test;
    std::shared_ptr<Weapon> w2Test;

    std::shared_ptr<Enemy> e3Test;
    std::shared_ptr<Weapon> w3Test;
public:
    MainMenuScene(Renderer& renderer, Scene** curr_scene_ptr) :
        renderer(renderer), curr_scene_ptr(curr_scene_ptr),
        text(Text::create<Text>(ResourceLoader::get_instance()->load_font("arial.ttf") , "Main Menu")),
        ysort(YSort::create<YSort>()),
        test(LevelWaves::create<LevelWaves>(ysort, "level1.lvl")),
        e1Test(Enemy::create<Enemy>(ysort, prototypes["Orc2"])),
        w1Test(Weapon::create<Weapon>(e1Test, "Bow", 8, sf::Vector2f(0, -10))),
        e2Test(Enemy::create<Enemy>(ysort, prototypes["Orc3"])),
        w2Test(Weapon::create<Weapon>(e2Test, "Staff", 8, sf::Vector2f(0, -10))),
        e3Test(Enemy::create<Enemy>(ysort, prototypes["Orc4"])),
        w3Test(Weapon::create<Weapon>(e3Test, "Sword", 8, sf::Vector2f(0, -10)))
    {
        e1Test->setTranslation({100, 100});
        e1Test->addNewWaypoint({500, 100});
        e1Test->addNewWaypoint({500, 400});
        e1Test->setScale(4);

        e2Test->setTranslation({100, 100});
        e2Test->addNewWaypoint({100, 500});
        e2Test->addNewWaypoint({400, 500});
        e2Test->setScale(4);

        e3Test->setTranslation({100, 100});
        e3Test->addNewWaypoint({600, 600});
        e3Test->setScale(4);

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
