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

    virtual myVec getPositionFromComp() const;
    virtual myVec getVelocityFromComp() const;

    virtual int getHalfWidth() const;
    virtual int getHalfHeight() const;

    virtual void updatePositionInComp(const myVec& position) const;
    virtual void setPositionInComp(const myVec& position) const;

    virtual void updateSprite(const std::string& direction, int animation) const;

    virtual void draw(sf::RenderTarget& target);


    //virtual functions for player class
    virtual int getHitPoints() const {return 0;}
    virtual void updateHitPoints(int damage) {}

    //virtual functions for zombie class
    virtual int getLastHit() const {return 0;};
    virtual void updateHitCooldown(int frame) {};

    friend std::ostream& operator<<(std::ostream& os, const Entity& rhs);
    Entity& operator=(const Entity& rhs);
};