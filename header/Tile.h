#pragma once

#include <memory>

#include "Components.h"
#include "myVec.h"

class Tile {
    std::shared_ptr<MotionComponent> m_cMotion;
    std::shared_ptr<SpriteComponent> m_cSprite;
public:
    Tile() = default;
    Tile(const myVec& position, const std::string& texture_path);
    ~Tile() = default;

    void draw(sf::RenderTarget& target);
};