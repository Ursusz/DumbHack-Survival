#pragma once
#include "../header/Entity.h"

class ComputeCollision {
    float deltaX = 0, deltaY = 0;
    float overlapX = 0, overlapY = 0;

public:
    void setOverlap(const Entity &e1, const Entity &e2);

    [[nodiscard]] bool isHorizontalOverlap() const;

    [[nodiscard]] bool isLeftOverlap() const;

    [[nodiscard]] bool isTopOverlap() const;

    [[nodiscard]] float getOverlapX() const;

    [[nodiscard]] float getOverlapY() const;
};
