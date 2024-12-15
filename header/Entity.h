#pragma once

#include <memory>
#include <utility>

#include "../header/Components.h"

#include <SFML/Graphics/RenderTarget.hpp>

class Entity {
    std::shared_ptr<MotionComponent> m_cMotion;
    std::shared_ptr<SpriteComponent> m_cSprite;
    std::shared_ptr<BoundingBoxComponent> m_cBoundingBox;
    sf::Sprite drawingSprite;
    const int change_animation_frame = 12;
    int current_frame = 0;
    int assets_pos_x = 0;
    bool m_hitAble = false;
    bool m_collidable = false;
    bool m_isDynamic = false;
protected:
    virtual bool canHit(int /*frame*/) = 0;
public:
    Entity() = default;
    Entity(const myVec& position, const myVec& velocity, const std::string& texture_path,
            bool hitAble, bool collidable, bool isDynamic);
    Entity(const Entity& rhs);
    virtual ~Entity() = default;

    myVec getPositionFromComp() const;
    myVec getVelocityFromComp() const;

    int getHalfWidth() const;
    int getHalfHeight() const;

    bool canTakeDamage() const;
    bool canCollide() const;
    void stopCollission();
    bool canMove() const;

    void updatePositionInComp(const myVec& position) const;
    void setPositionInComp(const myVec& position) const;

    void updateSprite(const std::string& direction) const;

    void changeAnimation();

    void draw(sf::RenderTarget& target);

    virtual void takeDamage(int /*damage*/) = 0;
    virtual void interactWith(Entity& other, int frame) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Entity& entity);
    friend void swap(Entity& e1, Entity& e2);
    virtual std::shared_ptr<Entity> clone() const = 0;
    Entity& operator=(const Entity& rhs);
};