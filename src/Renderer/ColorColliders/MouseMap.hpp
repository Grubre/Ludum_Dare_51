#pragma once
#include <unordered_map>
#include "Standard/event.hpp"
#include "Standard/Math/Hashers.hpp"
#include "Standard/math.hpp"
#include <SFML/Graphics.hpp>

class MouseMap
{
public:
    static MouseMap* get_instance();

private:
    static MouseMap* m_instance;

    std::unordered_map<sf::Color, std::weak_ptr<Node>> m_color_map;
    std::unordered_map<sf::Color, EventEmitter<engine::Vec2i>> on_hover;
    std::unordered_map<sf::Color, EventEmitter<engine::Vec2i>> on_click;

    void emit_hover(sf::Color color, engine::Vec2i mouse_pos) {
        if(on_hover.contains(color)){
            on_hover[color].emit(mouse_pos);
        }
    }
    void emit_click(sf::Color color, engine::Vec2i mouse_pos) {
        if(on_click.contains(color)){
            on_click[color].emit(mouse_pos);
        }
    }

public:
    void register_ptr(sf::Color color, std::weak_ptr<Node> ptr) {
        m_color_map[color] = ptr;
    }
    void register_hover(sf::Color color, EventListener<engine::Vec2i> listener) {
        EventEmitter<engine::Vec2i> ee;
        ee.subscribe(listener);
        on_hover[color] = ee;
    }
    void register_click(sf::Color color, EventListener<engine::Vec2i> listener) {
        EventEmitter<engine::Vec2i> ee;
        ee.subscribe(listener);
        on_click[color] = ee;
    }

    std::weak_ptr<Node> read_ptr(sf::Color color) {
        return m_color_map[color];
    }
};