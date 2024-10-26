#include "../header/Player.h"


Player::Player(const myVec &position, const myVec &velocity, const int width, const int height)
    : cMotion(std::make_shared<MotionComponent>(position, velocity))
    , cKeyboard(std::make_shared<KeyboardComponent>())
    , cShape(std::make_shared<ShapeComponent>(width, height))
{}

std::shared_ptr<KeyboardComponent> Player::getKeyboardComponent() const {
    return cKeyboard;
}

std::shared_ptr<MotionComponent> Player::getMotionComponent() const {
    return cMotion;
}

/// TODO : Maybe used later
// std::shared_ptr<ShapeComponent> Player::getShapeComponent() const {
//     return cShape;
// }

void Player::draw(sf::RenderTarget &target) {
    cShape->getShape().setPosition(cMotion->getPosition().getX(), cMotion->getPosition().getY());
    target.draw(cShape->getShape());
}
