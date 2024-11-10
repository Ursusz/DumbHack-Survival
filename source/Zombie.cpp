#include "../header/Zombie.h"

#include <SFML/Graphics/RenderTarget.hpp>

Zombie::Zombie(const myVec &position, const myVec &velocity, const std::string &texture_path)
    : m_cMotion(std::make_shared<MotionComponent>(position, velocity))
    , m_cSprite(std::make_shared<SpriteComponent>(texture_path))
    , m_cBoundingBox(std::make_shared<BoundingBoxComponent>(24, 24))
{}

Zombie::Zombie(const Zombie& rhs)
    : m_cMotion(rhs.m_cMotion)
    , m_cSprite(rhs.m_cSprite)
{}

myVec Zombie::getPositionFromComp() const {
    return m_cMotion->getPosition();
}

myVec Zombie::getVelocityFromComp() const {
    return m_cMotion->getVelocity();
}

void Zombie::setPositionInComp(const myVec &position) const {
    m_cMotion->setPosition(position);
}

int Zombie::getHalfWidth() const {
    return m_cBoundingBox->getHalfWidth();
}

int Zombie::getHalfHeight() const {
    return m_cBoundingBox->getHalfHeight();
}

void Zombie::draw(sf::RenderTarget& target){
    drawingSprite = m_cSprite->getSprite();
    drawingSprite.setPosition(m_cMotion->getPosition().getX(), m_cMotion->getPosition().getY());
    //Original sprite size is 16x16 so the middle of the sprite, before rescaling is 8, 8 from
    //the top left pixels
    drawingSprite.setOrigin(8, 8);
    target.draw(drawingSprite);
}

void Zombie::updateHitCooldown(int frame) {
    lastHit = frame;
}

int Zombie::getLastHit() const {
    return lastHit;
}

void Zombie::updatePosition(const myVec &playerPos) {
    direction = playerPos - m_cMotion->getPosition();
    //The zombie movement is the vector from the player to it. So if the direction is greater than 48 it means that the zombie
    //is next to the player. (the zombie and the player are both 16x16 and being scaled up to 3x, half the size of player and zombie is 16x3/2 = 24
    //so the distance between them should be 24 + 24 = 48 for the collision to take place)
    //Because they are not 16 pixels wide, only the sprite is, we are subtracting a padding of 12 pixels to look more like a real life collision)
    if(direction.length() > 48 - 12) {
        direction.normalize();
        direction *= 1.5f;
        m_cMotion->updatePosition(direction);
    }
    if(direction.getY() < 0 && std::abs(direction.getY()) > std::abs(direction.getX())) m_direction = "up";
    if(direction.getY() > 0 && std::abs(direction.getY()) > std::abs(direction.getX())) m_direction = "down";
    if(direction.getX() < 0 && std::abs(direction.getX()) > std::abs(direction.getY())) m_direction = "left";
    if(direction.getX() > 0 && std::abs(direction.getX()) > std::abs(direction.getY())) m_direction = "right";
}


void Zombie::updateSprite(int animation) const {
    //direction.length() is greater the closer the zombie is to the player
    //the direction is normalized and then multiplied by 2.0f, so when the zombie is next to the player
    //the direction would be much higher than 2, so we stop rendering animation for walking
    if(direction.length() < 1.5) {
        m_cSprite->updateSpriteComponent(m_direction, animation);
    }
}


Zombie& Zombie::operator=(const Zombie &rhs) {
    if(&rhs == this) {
        return *this;
    }
    m_cMotion = rhs.m_cMotion;
    m_cSprite = rhs.m_cSprite;
    m_cBoundingBox = rhs.m_cBoundingBox;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Zombie& rhs) {
    os << rhs.m_cMotion;
    return os;
}
