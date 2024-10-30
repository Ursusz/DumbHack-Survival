#include "../header/Player.h"


Player::Player(const myVec &position, const myVec &velocity, const std::string& texture_path)
    : m_cMotion(std::make_shared<MotionComponent>(position, velocity))
    , m_cKeyboard(std::make_shared<KeyboardComponent>())
    , m_cSprite(std::make_shared<SpriteComponent>(texture_path))
{}

Player::Player(const Player &rhs)
    : m_cMotion(rhs.m_cMotion)
    , m_cKeyboard(rhs.m_cKeyboard)
    , m_cSprite(rhs.m_cSprite)
{}

std::shared_ptr<KeyboardComponent> Player::getKeyboardComponent() const {
    return m_cKeyboard;
}

std::shared_ptr<MotionComponent> Player::getMotionComponent() const {
    return m_cMotion;
}

std::shared_ptr<SpriteComponent> Player::getSpriteComponent() const {
    return m_cSprite;
}

void Player::draw(sf::RenderTarget &target) {

    sf::Sprite drawingSprite = m_cSprite->getSprite();
    drawingSprite.setPosition(m_cMotion->getPosition().getX(), m_cMotion->getPosition().getY());
    drawingSprite.setOrigin(8, 8);
    target.draw(drawingSprite);
}

std::ostream& operator<<(std::ostream &os, const Player &player) {
    os << player.m_cMotion << player.m_cKeyboard;
    return os;
}

Player& Player::operator=(const Player &rhs) {
    m_cMotion = rhs.m_cMotion;
    m_cKeyboard = rhs.m_cKeyboard;
    m_cSprite = rhs.m_cSprite;
    return *this;
}