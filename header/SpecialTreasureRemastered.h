#pragma once

#include "../header/Tile.h"
#include "../header/Player.h"

class SpecialTreasureRemastered : public Tile{
    static std::string thisTyleType;
    bool canGive = true;
    bool canHit(int) override;
    void takeDamage(int) override;
public:
    SpecialTreasureRemastered() = default;
    SpecialTreasureRemastered(const myVec& position, const std::string& texture_path, bool hitAble, bool collidable, bool isDynamic, int drawPriority);

    void interactWith(Entity &other, int frame) override;
    void reset() override;

    SpecialTreasureRemastered& operator=(const SpecialTreasureRemastered& other);
};
