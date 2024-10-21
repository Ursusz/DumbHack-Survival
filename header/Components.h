#pragma once
#include "myVec.h"

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
};
