#pragma once

#include "../header/Components.h"
#include <memory>
#include <utility>
#include <SFML/Graphics/RenderTarget.hpp>

class Entity {
    std::shared_ptr<MotionComponent> m_cMotion;
    std::shared_ptr<SpriteComponent> m_cSprite;
    std::shared_ptr<BoundingBoxComponent> m_cBoundingBox;
    std::string m_EntityType;
    sf::Sprite drawingSprite;
    const int change_animation_frame = 12;
    int current_frame = 0;
    int assets_pos_x = 0;
public:
    Entity() = default;
    Entity(const myVec& position, const myVec& velocity, const std::string& texture_path, const std::string& entity_type);
    Entity(const Entity& rhs);
    virtual ~Entity() = default;

    myVec getPositionFromComp() const;
    myVec getVelocityFromComp() const;

    int getHalfWidth() const;
    int getHalfHeight() const;

    bool isType(const std::string& type) const;

    void updatePositionInComp(const myVec& position) const;
    void setPositionInComp(const myVec& position) const;

    void updateSprite(const std::string& direction) const;

    void changeAnimation();

    void draw(sf::RenderTarget& target);

    virtual bool canHit(int /*frame*/) = 0;
    virtual void takeDamage(int /*damage*/) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Entity& rhs);
    Entity& operator=(const Entity& rhs);
};