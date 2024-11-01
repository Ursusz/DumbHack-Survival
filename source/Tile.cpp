#include "../header/Tile.h"

#include <SFML/Graphics/RenderTarget.hpp>

Tile::Tile(const myVec &position, const std::string& texture_path)
    : m_cMotion(std::make_shared<MotionComponent>(position, myVec(0.0f, 0.0f)))
    , m_cSprite(std::make_shared<SpriteComponent>(texture_path))
{}

void Tile::draw(sf::RenderTarget &target) {
    sf::Sprite drawingSprite = m_cSprite->getSprite();
    drawingSprite.setPosition(m_cMotion->getPosition().getX(), m_cMotion->getPosition().getY());
    drawingSprite.setOrigin(8, 8);
    target.draw(drawingSprite);
}

std::ostream& operator<<(std::ostream& os, const Tile& tile) {
    os << tile.m_cMotion << std::endl;
    return os;
}


