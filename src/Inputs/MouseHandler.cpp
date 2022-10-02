#include "MouseHandler.hpp"
#include <cassert>

MouseHandler* MouseHandler::m_instance = nullptr;

void MouseHandler::initialize(std::shared_ptr<ColorMap> color_map) {
    m_instance = new MouseHandler(color_map);
}
MouseHandler::MouseHandler(std::shared_ptr<ColorMap> color_map){
    
}
MouseHandler* MouseHandler::get_instance()
{
    assert(m_instance != nullptr);
    return m_instance;
}
