#pragma once

#include <memory>
#include <string>
#include <utility>

#include "../header/Components.h"
#include "../header/Entity.h"
#include "../header/myVec.h"

class Tile : public Entity{
protected:
    std::string mutable tileType;
    bool canHit(int) override;
public:
    Tile() = default;
    Tile(const myVec& position, const std::string& texture_path, std::string& tileType, bool hitAble, bool collidable, bool isDynamic);
    ~Tile() override = default;

    void takeDamage(int damage) override;
    void interactWith(Entity &other, int frame) override;

    std::shared_ptr<Entity> clone() const override;

    friend std::ostream& operator<<(std::ostream& os, const Tile& tile);
    Tile& operator=(const Tile& rhs);
};