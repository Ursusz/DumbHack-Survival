#include "../header/ZombieBuilder.h"

ZombieBuilder &ZombieBuilder::setPosition(const myVec &newPosition) {
    this->position = newPosition;
    return *this;
}

ZombieBuilder &ZombieBuilder::setVelocity(const myVec &newVelocity) {
    this->velocity = newVelocity;
    return *this;
}

ZombieBuilder &ZombieBuilder::setTexturePath(const std::string &new_texture_path) {
    this->texture_path = new_texture_path;
    return *this;
}

ZombieBuilder &ZombieBuilder::setHitable(bool newHhitable) {
    this->hitable = newHhitable;
    return *this;
}

ZombieBuilder &ZombieBuilder::setCollidable(bool newCollidable) {
    this->collidable = newCollidable;
    return *this;
}

ZombieBuilder &ZombieBuilder::setIsDynamic(bool newisDynamic) {
    this->isDynamic = newisDynamic;
    return *this;
}

ZombieBuilder &ZombieBuilder::setDrawPriority(int newDrawPriority) {
    this->drawPriority = newDrawPriority;
    return *this;
}

std::shared_ptr<Zombie> ZombieBuilder::build() {
    return std::make_shared<Zombie>(position, velocity, texture_path, hitable, collidable, isDynamic, drawPriority);
}