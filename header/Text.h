#pragma once
#include <iostream>
#include <memory>

#include "../header/myVec.h"
#include "../header/Exceptions.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Text {
    std::shared_ptr<sf::Font> m_font;
    sf::Text m_text;
public:
    Text() = default;
    Text(const std::string& font_path,
            const std::string& text,
            size_t character_size,
            const sf::Color& color,
            const myVec& position);
    Text(const Text& rhs) = default;
    ~Text() = default;

    void drawText(sf::RenderTarget& target);
    Text& operator=(const Text& rhs);
};
