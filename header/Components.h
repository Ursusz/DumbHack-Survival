#pragma once
#include "../header/myVec.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

class MotionComponent {
    myVec m_position = {0.0f, 0.0f};
    myVec m_velocity = {0.0f, 0.0f};
public:
    MotionComponent() = default;
    MotionComponent(const myVec& position, const myVec& velocity)
        : m_position(position), m_velocity(velocity)
    {}
    ~MotionComponent() = default;

    myVec getPosition() const {
        return m_position;
    }

    myVec getVelocity() const {
        return m_velocity;
    }

    friend std::ostream& operator << (std::ostream& os, const MotionComponent& m) {
        os << "Position: " << m.m_position << " Velocity: " << m.m_velocity;
        return os;
    }

    void updatePosition(myVec& direction) {
        m_position += direction;
    }

    void updateVelocity(const myVec& velocity) {
        m_velocity = velocity;
    }
};

class KeyboardComponent {
    bool isUp = false;
    bool isDown = false;
    bool isLeft = false;
    bool isRight = false;
public:
    KeyboardComponent() = default;
    bool up() const {
        return isUp;
    }
    bool down() const {
        return isDown;
    }
    bool left() const {
        return isLeft;
    }
    bool right() const {
        return isRight;
    }

    void setUp(bool value) {
        isUp = value;
    }
    void setDown(bool value) {
        isDown = value;
    }
    void setLeft(bool value) {
        isLeft = value;
    }
    void setRight(bool value) {
        isRight = value;
    }
};

class ShapeComponent {
    sf::RectangleShape m_shape;
public:
    ShapeComponent() = default;
    ShapeComponent(const int width, const int height) : m_shape(sf::Vector2f(width, height)) {}

    sf::RectangleShape& getShape() {
        return m_shape;
    }
};