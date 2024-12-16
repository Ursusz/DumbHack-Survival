#pragma once

#include <string>

#include "../header/Tile.h"
#include "../header/Player.h"

#include <SFML/Audio/Music.hpp>

class AnimatedTile : public Tile{
    sf::Music music;
    static std::string thisTyleType;
    bool canHit(int) override;
    void takeDamage(int) override;
public:
    AnimatedTile() = default;
    AnimatedTile(const myVec& position, const std::string& texture_path, bool hitAble, bool collidable, bool isDynamic, int drawPriority, const std::string& musicFilePath);

    void interactWith(Entity &other, int frame) override;

    AnimatedTile& operator=(const AnimatedTile& other);
};
