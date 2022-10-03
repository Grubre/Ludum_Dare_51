#pragma once
#include "GUI/GUI.hpp"
#include "Standard/config.hpp"
#include "Loaders/ResourceLoader.hpp"

class Text : public GUI{
public:
    explicit Text(std::shared_ptr<sf::Font> font, const std::string &text = "");

    sf::Text& text();
protected:
    void onUpdate([[maybe_unused]] const sf::Time& delta) override;
    void onDraw([[maybe_unused]]Renderer &renderer) const override;

private:
    std::shared_ptr<sf::Font> font;
    sf::Text m_text;
};
