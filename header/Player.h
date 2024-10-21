#pragma once
#include <memory>

#include "../header/Components.h"

class Player {
    std::shared_ptr<MotionComponent> cMotion;
public:
    Player() = default;
    Player(const myVec& position, const myVec& velocity);
};