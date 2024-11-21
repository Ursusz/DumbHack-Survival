#include "../header/Player.h"


Player::Player(const myVec &position, const myVec &velocity, const std::string& texture_path, const std::string& entity_type)
    : Entity(position, velocity, texture_path, entity_type)
    , m_cKeyboard(std::make_shared<KeyboardComponent>())
    , heartSprite(std::make_shared<SpriteComponent>("assets/heart.png"))
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

void Player::takeDamage(int damage) {
    if(hitPoints > 0) {
        hitPoints -= damage;
    }
}

bool Player::canHit(int frame) {
    if(lastHit == 0 || frame - lastHit > 60) {
        lastHit = frame;
        return true;
    }
    return false;
}

bool Player::isEnemyInFront(const myVec &enemyPos, const myVec &playerDirection, float range, float angleThreshHold) {
    if(this->getPositionFromComp().distance(enemyPos) > range) return false;
    myVec playerToEnemyVec = (this->getPositionFromComp()-enemyPos);
    playerToEnemyVec.normalize();

    float dotProduct = playerToEnemyVec.getX() * playerDirection.getX() + playerToEnemyVec.getY() * playerDirection.getY();

    float cosAngle = std::cos(angleThreshHold) * (3.14159f / 180.0f);
    return dotProduct <= cosAngle;
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

void Player::drawHP(sf::RenderTarget &m_window) {
    for(int i = 0; i < std::ceil((float)hitPoints/20.0f); i++) {
        hearts[i] = heartSprite->getSprite();
        hearts[i].setOrigin(8, 8);
        hearts[i].setScale(1, 1);
        hearts[i].setPosition(Entity::getPositionFromComp().getX() - 26 + i*12, Entity::getPositionFromComp().getY()-48);
        if(hitPoints%20 != 0) {
            hearts[hitPoints/20].setTextureRect(sf::IntRect(17, 0, 16, 16));
        }
        m_window.draw(hearts[i]);
    }
}

bool Player::isInComputerRange() const {
    if(this->getPositionFromComp().distance(myVec(888, 552)) < 200) return true;
    return false;
}


Player& Player::operator=(const Player &rhs) {
    if(&rhs == this) {
        return *this;
    }
    Entity::operator=(rhs);
    m_cKeyboard = rhs.m_cKeyboard;
    heartSprite = rhs.heartSprite;
    hitPoints = 100;
    lastHit = 0;
    return *this;
}