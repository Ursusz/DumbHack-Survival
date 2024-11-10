#include "../header/Player.h"


Player::Player(const myVec &position, const myVec &velocity, const std::string& texture_path)
    : m_cMotion(std::make_shared<MotionComponent>(position, velocity))
    , m_cKeyboard(std::make_shared<KeyboardComponent>())
    , m_cSprite(std::make_shared<SpriteComponent>(texture_path))
    , m_cBoundingBox(std::make_shared<BoundingBoxComponent>(24, 24))
{}

Player::Player(const Player &rhs)
    : m_cMotion(rhs.m_cMotion)
    , m_cKeyboard(rhs.m_cKeyboard)
    , m_cSprite(rhs.m_cSprite)
    , m_cBoundingBox(rhs.m_cBoundingBox)
{}

myVec Player::getVelocityFromComp() const {
    return m_cMotion->getVelocity();
}

myVec Player::getPositionFromComp() const {
    return m_cMotion->getPosition();
}

int Player::getHalfWidth() const {
    return m_cBoundingBox->getHalfWidth();
}

int Player::getHalfHeight() const {
    return m_cBoundingBox->getHalfHeight();
}

void Player::updatePositionInComp(const myVec &position) const {
    m_cMotion->updatePosition(position);
}

void Player::setPositionInComp(const myVec &position) const {
    m_cMotion->setPosition(position);
}


bool Player::isKeyUp() const {
    return m_cKeyboard->up();
}

bool Player::isKeyDown() const {
    return m_cKeyboard->down();
}

bool Player::isKeyLeft() const {
    return m_cKeyboard->left();
}

bool Player::isKeyRight() const {
    return m_cKeyboard->right();
}

void Player::updateHitPoints(float damage) {
    hitPoints -= damage;
}

int Player::getHitPoitns() const {
    return hitPoints;
}


void Player::updateSprite(const std::string &direction, int animation) const {
    m_cSprite->updateSpriteComponent(direction, animation);
}

void Player::setKeyValue(int key, bool toggle) {
    switch(key) {
        case 0:
            m_cKeyboard->setUp(toggle);
            break;
        case 1:
            m_cKeyboard->setDown(toggle);
            break;
        case 2:
            m_cKeyboard->setLeft(toggle);
            break;
        case 3:
            m_cKeyboard->setRight(toggle);
            break;
        default: break;
    }
}

void Player::draw(sf::RenderTarget &target) {
    drawingSprite = m_cSprite->getSprite();
    drawingSprite.setPosition(m_cMotion->getPosition().getX(), m_cMotion->getPosition().getY());
    drawingSprite.setOrigin(8, 8);
    target.draw(drawingSprite);
}

std::ostream& operator<<(std::ostream &os, const Player &player) {
    os << player.m_cMotion << player.m_cKeyboard;
    return os;
}

Player& Player::operator=(const Player &rhs) {
    if(&rhs == this) {
        return *this;
    }

    m_cMotion = rhs.m_cMotion;
    m_cKeyboard = rhs.m_cKeyboard;
    m_cSprite = rhs.m_cSprite;
    m_cBoundingBox = rhs.m_cBoundingBox;
    return *this;
}