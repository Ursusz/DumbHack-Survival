#include "../header/Text.h"

Text::Text(const std::string& font_path,
           const std::string& text,
           size_t character_size,
           const sf::Color& color,
           const myVec& position)
    : m_font(std::make_shared<sf::Font>())
{
    if(!m_font->loadFromFile(font_path)) {
        std::cerr << "Failed to load font" << std::endl;
    }
    m_text.setFont(*m_font);
    m_text.setString(text);
    m_text.setCharacterSize(character_size);
    m_text.setFillColor(color);
    m_text.setStyle(sf::Text::Bold);
    m_text.setOrigin(m_text.getLocalBounds().width/2, m_text.getLocalBounds().height/2);
    m_text.setPosition(position.getX(), position.getY());
}

void Text::drawText(sf::RenderTarget &target) {
    m_text.setPosition(m_text.getPosition());
    target.draw(m_text);
}

void Text::updateTextContent(const std::string &text) {
    m_text.setString(text);
}

Text& Text::operator=(const Text &rhs) {
    if(&rhs == this) {
        return *this;
    }
    m_font = rhs.m_font;
    m_text = rhs.m_text;
    return *this;
}