#include "Text.hpp"

Text::Text(std::shared_ptr<sf::Font> font, const std::string &text) : font(font) {
    this->m_text.setFont(*font);
    this->m_text.setString(text);
    this->m_text.setCharacterSize(engine::config::default_font_size);
}

sf::Text& Text::text(){
    return m_text;
}

void Text::onUpdate([[maybe_unused]] const sf::Time& delta){

}

void Text::onDraw([[maybe_unused]]Renderer &renderer) const{
    renderer.draw_object_on_layer(m_text, 1);
}

