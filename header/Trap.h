#pragma once

#include "../header/Tile.h"

#include <string>

#include <SFML/Graphics/RenderTarget.hpp>

class Trap : public Tile{
    static std::string thisTileType;
protected:
    int damage = 40;
    bool isSet = true;
public:
    Trap() = default;
    Trap(const myVec& position, const std::string& texture_path, bool hitAble, bool collidable, bool isDynamic, int drawPriority);
    ~Trap() override = default;

    bool canHit(int /*frame*/) override;
    void takeDamage(int /*damage*/) override;
    void interactWith(Entity &other, int frame) override;

    using Entity::draw;
    void draw(sf::RenderTarget& target, int frame);

    Trap& operator=(const Trap& other);
};