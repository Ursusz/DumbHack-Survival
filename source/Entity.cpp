#include <utility>

#include "../header/Entity.h"

Entity::Entity(const myVec &position, const myVec &velocity, const std::string& texture_path, bool hitAble, bool collidable, bool isDynamic)
    : m_cMotion(std::make_shared<MotionComponent>(position, velocity))
    , m_cSprite(std::make_shared<SpriteComponent>(texture_path))
    , m_cBoundingBox(std::make_shared<BoundingBoxComponent>(24, 24))
    , m_hitAble(hitAble)
    , m_collidable(collidable)
    , m_isDynamic(isDynamic)
{   }

Entity::Entity(const Entity &rhs)
    : m_cMotion(rhs.m_cMotion ? rhs.m_cMotion->clone() : nullptr)
    , m_cSprite(rhs.m_cSprite ? rhs.m_cSprite->clone() : nullptr)
    , m_cBoundingBox(rhs.m_cBoundingBox ? rhs.m_cBoundingBox->clone() : nullptr)
    , m_hitAble(rhs.m_hitAble)
    , m_collidable(rhs.m_collidable)
    , m_isDynamic(rhs.m_isDynamic)
{}

myVec Entity::getVelocityFromComp() const {
    return m_cMotion->getVelocity();
}

myVec Entity::getPositionFromComp() const {
    return m_cMotion->getPosition();
}

int Entity::getHalfWidth() const {
    return m_cBoundingBox->getHalfWidth();
}

int Entity::getHalfHeight() const {
    return m_cBoundingBox->getHalfHeight();
}

bool Entity::canTakeDamage() const {
    return m_hitAble;
}

bool Entity::canCollide() const {
    return m_collidable;
}

bool Entity::canMove() const {
    return m_isDynamic;
}

void Entity::updatePositionInComp(const myVec &position) const {
    m_cMotion->updatePosition(position);
}

void Entity::setPositionInComp(const myVec &position) const {
    m_cMotion->setPosition(position);
}

void Entity::changeAnimation() {
    current_frame++;
    if(current_frame > change_animation_frame) {
        assets_pos_x = (assets_pos_x == 0) ? 16 : 0;
        current_frame = 0;
    }
}

void Entity::draw(sf::RenderTarget &target){
    drawingSprite = m_cSprite->getSprite();
    drawingSprite.setPosition(m_cMotion->getPosition().getX(), m_cMotion->getPosition().getY());
    drawingSprite.setOrigin(8, 8);
    target.draw(drawingSprite);
}

void Entity::updateSprite(const std::string &direction) const {
    m_cSprite->updateSpriteComponent(direction, assets_pos_x);
}

std::ostream& operator<<(std::ostream &os, const Entity &entity) {
    os << entity.m_cMotion << " " << entity.change_animation_frame << " ";
    return os;
}

void swap(Entity &e1, Entity &e2) {
    using std::swap;
    swap(e1.m_cMotion, e2.m_cMotion);
    swap(e1.m_cSprite, e2.m_cSprite);
    swap(e1.m_cBoundingBox, e2.m_cBoundingBox);
    swap(e1.current_frame, e2.current_frame);
    swap(e1.assets_pos_x, e2.assets_pos_x);
    swap(e1.m_hitAble, e2.m_hitAble);
    swap(e1.m_collidable, e2.m_collidable);
    swap(e1.m_isDynamic, e2.m_isDynamic);
}

Entity& Entity::operator=(const Entity& rhs) {
    auto copy = rhs.clone();
    using std::swap;
    swap(*this, *copy);
    return *this;
}