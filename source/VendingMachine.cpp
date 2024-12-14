#include "../header/VendingMachine.h"

VendingMachine::VendingMachine(const myVec &position, const myVec &velocity, const std::string &texture_path,
                                bool hitAble, bool collidable, bool isDynamic)
    : Entity(position, velocity, texture_path, hitAble, collidable, isDynamic) {
}

VendingMachine::VendingMachine(const Entity &rhs)
    : Entity(rhs) {
}

void VendingMachine::takeDamage(int /*damage*/) {}

bool VendingMachine::canHit(int frame) {
    (void)frame;
    if (numOfDoses > 0) {
        float elapsedTime = clock.getElapsedTime().asSeconds();
        if((elapsedTime - lastUsedTime >= 30.f && lastUsedTime != 0.0f) || lastUsedTime == 0.0f) {
            lastUsedTime = elapsedTime;
            return true;
        }
    }
    return false;
}

void VendingMachine::interactWith(Entity &other, int frame) {
    if(this->canHit(frame) && other.canTakeDamage()) {
        numOfDoses--;
        other.takeDamage(-10);
    }
}

std::shared_ptr<Entity> VendingMachine::clone() const {
    return std::make_shared<VendingMachine>(*this);
}