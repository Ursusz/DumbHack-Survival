#pragma once

#include <memory>

#include "../header/myVec.h"
#include "../header/Zombie.h"

class ZombieBuilder {
    myVec position;
    myVec velocity;
    std::string texture_path;
    bool hitable=true, collidable=true, isDynamic=true;
    int drawPriority=1;
public:
    ZombieBuilder& setPosition(const myVec& newPosition);
    ZombieBuilder& setVelocity(const myVec& newVelocity);
    ZombieBuilder& setTexturePath(const std::string& new_texture_path);
    ZombieBuilder& setHitable(bool newHhitable);
    ZombieBuilder& setCollidable(bool newCollidable);
    ZombieBuilder& setIsDynamic(bool newisDynamic);
    ZombieBuilder& setDrawPriority(int newDrawPriority);

    std::shared_ptr<Zombie> build();
};