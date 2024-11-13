#include "../header/Entity.h"

Entity::Entity(const myVec &position, const myVec &velocity, const std::string& texture_path)
    : m_cMotion(std::make_shared<MotionComponent>(position, velocity))
    , m_cSprite(std::make_shared<SpriteComponent>(texture_path))
    , m_cBoundingBox(std::make_shared<BoundingBoxComponent>(24, 24))
{}

Entity::Entity(const Entity &rhs)
    : m_cMotion(rhs.m_cMotion)
    , m_cSprite(rhs.m_cSprite)
    , m_cBoundingBox(rhs.m_cBoundingBox)
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

void Entity::updatePositionInComp(const myVec &position) const {
    m_cMotion->updatePosition(position);
}

void Entity::setPositionInComp(const myVec &position) const {
    m_cMotion->setPosition(position);
}

void Entity::draw(sf::RenderTarget &target){
    drawingSprite = m_cSprite->getSprite();
    drawingSprite.setPosition(m_cMotion->getPosition().getX(), m_cMotion->getPosition().getY());
    drawingSprite.setOrigin(8, 8);
    target.draw(drawingSprite);
}

void Entity::updateSprite(const std::string &direction, int animation) const {
    m_cSprite->updateSpriteComponent(direction, animation);
}

std::ostream& operator<<(std::ostream &os, const Entity &entity) {
    os << entity.m_cMotion << std::endl;
    return os;
}

Entity& Entity::operator=(const Entity &rhs) {
    if(&rhs == this) {
        return *this;
    }
    m_cMotion = rhs.m_cMotion;
    // m_cKeyboard = rhs.m_cKeyboard;
    m_cSprite = rhs.m_cSprite;
    m_cBoundingBox = rhs.m_cBoundingBox;
    return *this;
}