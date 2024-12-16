#include "../header/Trap.h"

#include "../header/Player.h"

std::string Trap::thisTileType = "trap";

Trap::Trap(const myVec &position, const std::string &texture_path, bool hitAble, bool collidable, bool isDynamic, int drawPriority)
    : Tile(position, texture_path, thisTileType, hitAble, collidable, isDynamic, drawPriority) {}


bool Trap::canHit(int frame) {
    if (frame > 600) {
        return true;
    }
    return false;
}

void Trap::takeDamage(int) {}

void Trap::interactWith(Entity &other, int frame) {
    if(auto playerptr = dynamic_cast<Player*> (&other)) {
        if(this->canHit(frame) && isSet) {
            playerptr->takeDamage(damage);
            isSet = false;
            stopCollission();
        }
    }
}

void Trap::draw(sf::RenderTarget &target, int frame) {
    if(frame > 600 && isSet) {
        Entity::draw(target);
    }
}


Trap& Trap::operator=(const Trap &other) {
    if (this != &other) {
        Entity::operator=(other);
        damage = other.damage;
        isSet = other.isSet;
        this->tileType = other.tileType;
    }
    return *this;
}