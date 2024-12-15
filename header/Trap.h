#pragma once

#include "../header/Tile.h"

#include <string>

#include <SFML/Graphics/RenderTarget.hpp>

class Trap : public Tile{
    int damage = 40;
    bool isSet = true;
    static std::string thisTileType;
public:
    Trap() = default;
    Trap(const myVec& position, const std::string& texture_path, bool hitAble, bool collidable, bool isDynamic);
    ~Trap() override = default;

    bool canHit(int /*frame*/) override;
    void takeDamage(int /*damage*/) override;
    void interactWith(Entity &other, int frame) override;

    void draw(sf::RenderTarget& target, int frame);

    Trap& operator=(const Trap& other);
};
