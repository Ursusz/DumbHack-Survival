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
    ZombieBuilder& setPosition(const myVec& position);
    ZombieBuilder& setVelocity(const myVec& velocity);
    ZombieBuilder& setTexturePath(const std::string& texture_path);
    ZombieBuilder& setHitable(bool hitable);
    ZombieBuilder& setCollidable(bool collidable);
    ZombieBuilder& setIsDynamic(bool isDynamic);
    ZombieBuilder& setDrawPriority(int drawPriority);

    std::shared_ptr<Zombie> build();
};