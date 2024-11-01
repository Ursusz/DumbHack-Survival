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

void Zombie::draw(sf::RenderTarget& target){
    sf::Sprite sprite = m_cSprite->getSprite();
    sprite.setPosition(m_cMotion->getPosition().getX(), m_cMotion->getPosition().getY());
    //Original sprite size is 16x16 so the middle of the sprite, before rescaling is 8, 8 from
    //the top left pixels
    sprite.setOrigin(8, 8);
    target.draw(sprite);
}

void Zombie::updatePosition(const myVec &playerPos) {
    myVec direction = playerPos - m_cMotion->getPosition();
    //Original sprite size is 16, it is scaled x3 so the new size is 48x48
    //the distance between the origin of my player and the origin of my zombie
    //is the sum of half their size in each direction, 48/2 + 48/2 = 48
    if(direction.length() > 48) {
        direction.normalize();
        direction *= 2.0f;
        m_cMotion->updatePosition(direction);
    }
}

Zombie& Zombie::operator=(const Zombie &rhs) {
    if(&rhs == this) {
        return *this;
    }
    m_cMotion = rhs.m_cMotion;
    m_cSprite = rhs.m_cSprite;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Zombie& rhs) {
    os << rhs.m_cMotion;
    return os;
}