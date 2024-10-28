#include "../header/Zombie.h"

#include <SFML/Graphics/RenderTarget.hpp>

Zombie::Zombie(const myVec &position, const myVec &velocity, const std::string &texture_path)
    : m_cMotion(std::make_shared<MotionComponent>(position, velocity))
    , m_cSprite(std::make_shared<SpriteComponent>(texture_path))
{}
Zombie::Zombie(const Zombie& rhs)
    : m_cMotion(rhs.m_cMotion)
    , m_cSprite(rhs.m_cSprite)
{}

std::shared_ptr<MotionComponent> Zombie::getMotionComponent() const {
    return m_cMotion;
}

std::shared_ptr<SpriteComponent> Zombie::getSpriteComponent() const {
    return m_cSprite;
}

void Zombie::draw(sf::RenderTarget& target){
    sf::Sprite sprite = m_cSprite->getSprite();
    sprite.setPosition(m_cMotion->getPosition().getX(), m_cMotion->getPosition().getY());
    target.draw(sprite);
}

void Zombie::updatePosition(const myVec &playerPos) {
    myVec direction = playerPos - m_cMotion->getPosition();
    if(direction.length() > 48) {
        direction.normalize();
        direction *= 2.0f;
        m_cMotion->updatePosition(direction);
    }
}

Zombie& Zombie::operator=(const Zombie &rhs) {
    m_cMotion = rhs.m_cMotion;
    m_cSprite = rhs.m_cSprite;
    return *this;
}