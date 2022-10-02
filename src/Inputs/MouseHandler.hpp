#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer/ColorMap.hpp"
#include <memory>

class MouseHandler {
    public:
        static MouseHandler* get_instance();
        static void initialize(std::shared_ptr<ColorMap> color_map);

    private:
        static MouseHandler* m_instance;

        MouseHandler(std::shared_ptr<ColorMap> color_map);

        std::shared_ptr<ColorMap> color_map;

};