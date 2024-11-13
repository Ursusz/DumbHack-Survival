#pragma once

#include "../header/Components.h"
#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>

class Entity {
    std::shared_ptr<MotionComponent> m_cMotion;
    std::shared_ptr<SpriteComponent> m_cSprite;
    std::shared_ptr<BoundingBoxComponent> m_cBoundingBox;
    sf::Sprite drawingSprite;
public:
    Entity() = default;
    Entity(const myVec& position, const myVec& velocity, const std::string& texture_path);
    Entity(const Entity& rhs);
    virtual ~Entity() = default;

    myVec getPositionFromComp() const;
    myVec getVelocityFromComp() const;

    int getHalfWidth() const;
    int getHalfHeight() const;

    void updatePositionInComp(const myVec& position) const;
    void setPositionInComp(const myVec& position) const;

    void updateSprite(const std::string& direction, int animation) const;

    void draw(sf::RenderTarget& target);

    //virtual functions for player class
    virtual int getHitPoints() const {return 0;}
    virtual void updateHitPoints(int) {}

    //virtual functions for zombie class
    virtual int getLastHit() const {return 0;};
    virtual void updateHitCooldown(int) {}

    friend std::ostream& operator<<(std::ostream& os, const Entity& rhs);
    Entity& operator=(const Entity& rhs);
};