#pragma once
#include <memory>

#include "../header/Components.h"
#include <SFML/Graphics/RenderTarget.hpp>

class Player {
    std::shared_ptr<MotionComponent> cMotion;
    std::shared_ptr<KeyboardComponent> cKeyboard;
    std::shared_ptr<ShapeComponent> cShape;

public:
    Player() = default;
    Player(const myVec& position, const myVec& velocity, const int width, const int height);

    std::shared_ptr<MotionComponent> getMotionComponent() const;
    std::shared_ptr<KeyboardComponent> getKeyboardComponent() const;
    std::shared_ptr<ShapeComponent> getShapeComponent() const;

    void draw(sf::RenderTarget& target);
};
