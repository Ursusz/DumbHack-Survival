#include "../header/Player.h"


Player::Player(const myVec &position, const myVec &velocity)
    : cMotion(std::make_shared<MotionComponent>(position, velocity))
{}
