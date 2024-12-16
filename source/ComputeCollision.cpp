#include "../header/ComputeCollision.h"

void ComputeCollision::setOverlap(const Entity& e1, const Entity& e2) {
    if(e1.canCollide() && e2.canCollide()) {
        deltaX = e1.getPositionFromComp().getX() - e2.getPositionFromComp().getX();
        deltaY = e1.getPositionFromComp().getY() - e2.getPositionFromComp().getY();

        overlapX = (e1.getHalfWidth() + e2.getHalfWidth()) - std::abs(deltaX);
        overlapY = (e1.getHalfHeight() + e2.getHalfHeight()) - std::abs(deltaY);
    }
}

bool ComputeCollision::isHorizontalOverlap() const {
    return overlapX < overlapY;
}

bool ComputeCollision::isLeftOverlap() const {
    return deltaX > 0.0f;
}

bool ComputeCollision::isTopOverlap() const {
    return deltaY > 0.0f;
}

float ComputeCollision::getOverlapX() const {
    return overlapX;
}

float ComputeCollision::getOverlapY() const {
    return overlapY;
}
