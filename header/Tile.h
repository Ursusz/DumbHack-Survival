#pragma once

#include <memory>

#include "Components.h"
#include "myVec.h"

class Tile {
    std::shared_ptr<MotionComponent> m_cMotion;
    std::shared_ptr<SpriteComponent> m_cSprite;
    std::shared_ptr<BoundingBoxComponent> m_cBoundingBox;
public:
    Tile() = default;
    Tile(const myVec& position, const std::string& texture_path);
    ~Tile() = default;

    int getHalfWidth() const;
    int getHalfHeight() const;

    friend std::ostream& operator<<(std::ostream& os, const Tile& tile);
    void draw(sf::RenderTarget& target);
};