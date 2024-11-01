#pragma once
#include <memory>

#include "Components.h"

class Zombie {
    std::shared_ptr<MotionComponent> m_cMotion;
    std::shared_ptr<SpriteComponent> m_cSprite;
public:
    Zombie() = default;
    Zombie(const myVec& position, const myVec& velocity, const std::string& texture_path);
    Zombie(const Zombie& rhs);
    ~Zombie() = default;

    void draw(sf::RenderTarget& target);

    void updatePosition(const myVec& playerPos);

    friend std::ostream& operator<<(std::ostream& os, const Zombie& zombie);
    Zombie& operator=(const Zombie& zombie);
};
