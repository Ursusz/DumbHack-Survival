#include "../header/Collision.h"

void Collision::setOverlap(const Entity& e1, const Entity& e2) {
    deltaX = e1.getPositionFromComp().getX() - e2.getPositionFromComp().getX();
    deltaY = e1.getPositionFromComp().getY() - e2.getPositionFromComp().getY();

    overlapX = (e1.getHalfWidth() + e2.getHalfWidth()) - std::abs(deltaX);
    overlapY = (e1.getHalfHeight() + e2.getHalfHeight()) - std::abs(deltaY);
}

bool Collision::isHorizontalOverlap() const {
    return overlapX < overlapY;
}

bool Collision::isLeftOverlap() const {
    return deltaX > 0.0f;
}

bool Collision::isTopOverlap() const {
    return deltaY > 0.0f;
}

float Collision::getOverlapX() const {
    return overlapX;
}

float Collision::getOverlapY() const {
    return overlapY;
}
