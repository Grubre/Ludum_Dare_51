#pragma once
#include <cstdint>
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "Loaders/ResourceLoader.hpp"

namespace engine
{
    struct config{
        static constexpr uint32_t window_width  = 1600;
        static constexpr uint32_t window_height = 800;
        static constexpr uint32_t default_font_size = 32;
    };
}
