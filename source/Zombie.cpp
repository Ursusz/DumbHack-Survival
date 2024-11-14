#include "../header/Zombie.h"

#include <SFML/Graphics/RenderTarget.hpp>

Zombie::Zombie(const myVec &position, const myVec &velocity, const std::string &texture_path, const std::string& entity_type)
    : Entity(position, velocity, texture_path, entity_type)
{}

Zombie::Zombie(const Zombie& rhs)
    : Entity(rhs)
{}

std::string &Zombie::getDirection() {
    return m_direction;
}


void Zombie::updateHitCooldown(int frame) {
    lastHit = frame;
}

int Zombie::getLastHit() const {
    return lastHit;
}

void Zombie::followPlayer(const myVec &playerPos) {
    direction = playerPos - this->getPositionFromComp();
    //The zombie movement is the vector from the player to it. So if the direction is greater than 48 it means that the zombie
    //is next to the player. (the zombie and the player are both 16x16 and being scaled up to 3x, half the size of player and zombie is 16x3/2 = 24
    //so the distance between them should be 24 + 24 = 48 for the collision to take place)
    //Because they are not 16 pixels wide, only the sprite is, we are subtracting a padding of 12 pixels to look more like a real life collision)
    if(direction.length() > 50) {
        direction.normalize();
        direction *= 1.5f;
        this->updatePositionInComp(direction);
    }
    if(direction.getY() < 0 && std::abs(direction.getY()) > std::abs(direction.getX())) m_direction = "up";
    if(direction.getY() > 0 && std::abs(direction.getY()) > std::abs(direction.getX())) m_direction = "down";
    if(direction.getX() < 0 && std::abs(direction.getX()) > std::abs(direction.getY())) m_direction = "left";
    if(direction.getX() > 0 && std::abs(direction.getX()) > std::abs(direction.getY())) m_direction = "right";
}

Zombie& Zombie::operator=(const Zombie &rhs) {
    if(&rhs == this) {
        return *this;
    }
    Entity::operator=(rhs);
    lastHit = rhs.lastHit;
    return *this;
}
