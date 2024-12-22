#include "../header/SpecialTreasureRemastered.h"

std::string SpecialTreasureRemastered::thisTyleType = "specialTreasure";

SpecialTreasureRemastered::SpecialTreasureRemastered(const myVec &position, const std::string &texture_path, bool hitAble, bool collidable, bool isDynamic, int drawPriority)
    : Tile(position, texture_path, thisTyleType, hitAble, collidable, isDynamic, drawPriority) {
}

bool SpecialTreasureRemastered::canHit(int) {
    return canGive;
}

void SpecialTreasureRemastered::takeDamage(int) {}

void SpecialTreasureRemastered::interactWith(Entity &other, int frame) {
    if(auto playerPtr = dynamic_cast<Player*> (&other)) {
        if(canHit(frame)) {
            playerPtr->takeBonus(20, "damage");
            canGive = false;
        }
    }
}

SpecialTreasureRemastered& SpecialTreasureRemastered::operator=(const SpecialTreasureRemastered &other) {
    if(this != &other) {
        Entity::operator=(other);
        this->thisTyleType = other.thisTyleType;
    }
    return *this;
}