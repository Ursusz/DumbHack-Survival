#include "../header/Player.h"


Player::Player(const myVec &position, const myVec &velocity, const std::string& texture_path)
    : Entity(position, velocity, texture_path)
    , m_cKeyboard(std::make_shared<KeyboardComponent>())
{}

Player::Player(const Player &rhs)
    : Entity(rhs)
    , m_cKeyboard(rhs.m_cKeyboard)
{}


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

bool Player::isAlive() const {
    return hitPoints != 0;
}


void Player::updateHitPoints(int damage) {
    hitPoints -= damage;
}

int Player::getHitPoints() const {
    return hitPoints;
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

Player& Player::operator=(const Player &rhs) {
    if(&rhs == this) {
        return *this;
    }
    Entity::operator=(rhs);
    m_cKeyboard = rhs.m_cKeyboard;
    hitPoints = rhs.hitPoints;
    return *this;
}