#include "../header/ZombieBuilder.h"

ZombieBuilder &ZombieBuilder::setPosition(const myVec &position) {
    this->position = position;
    return *this;
}

ZombieBuilder &ZombieBuilder::setVelocity(const myVec &velocity) {
    this->velocity = velocity;
    return *this;
}

ZombieBuilder &ZombieBuilder::setTexturePath(const std::string &texture_path) {
    this->texture_path = texture_path;
    return *this;
}

ZombieBuilder &ZombieBuilder::setHitable(bool hitable) {
    this->hitable = hitable;
    return *this;
}

ZombieBuilder &ZombieBuilder::setCollidable(bool collidable) {
    this->collidable = collidable;
    return *this;
}

ZombieBuilder &ZombieBuilder::setIsDynamic(bool isDynamic) {
    this->isDynamic = isDynamic;
    return *this;
}

ZombieBuilder &ZombieBuilder::setDrawPriority(int drawPriority) {
    this->drawPriority = drawPriority;
    return *this;
}

std::shared_ptr<Zombie> ZombieBuilder::build() {
    return std::make_shared<Zombie>(position, velocity, texture_path, hitable, collidable, isDynamic, drawPriority);
}