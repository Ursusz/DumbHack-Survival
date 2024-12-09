#include "../header/VendingMachine.h"

VendingMachine::VendingMachine(const myVec &position, const myVec &velocity, const std::string &texture_path,
    const std::string &entity_type)
    : Entity(position, velocity, texture_path, entity_type) {
}

VendingMachine::VendingMachine(const Entity &rhs)
    : Entity(rhs) {
}

int VendingMachine::takeDose() {
    if (numOfDoses > 0) {
        float elapsedTime = clock.getElapsedTime().asSeconds();
        if(elapsedTime - lastUsedTime >= 30.f && lastUsedTime != 0.0f) {
            lastUsedTime = elapsedTime;
            numOfDoses--;
            return 10; ///this vending machine gifts the player whatever juice which gives him 10 hp once every 30 seconds if hit
        }
        if (lastUsedTime == 0.0f) {
            lastUsedTime = elapsedTime;
            numOfDoses--;
            return 10;
        }
    }
    return 0;
}
void VendingMachine::takeDamage(int /*damage*/) {}

bool VendingMachine::canHit(int /*frame*/) {return false;}

std::shared_ptr<Entity> VendingMachine::clone() const {
    return std::make_shared<VendingMachine>(*this);
}