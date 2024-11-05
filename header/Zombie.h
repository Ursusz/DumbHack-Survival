#pragma once
#include <memory>

#include "Components.h"

class Zombie {
    std::shared_ptr<MotionComponent> m_cMotion;
    std::shared_ptr<SpriteComponent> m_cSprite;
    std::string m_direction;    //this is the string that sets the zombie to look at a direction
    myVec direction;    //this is the direction vector
public:
    Zombie() = default;
    Zombie(const myVec& position, const myVec& velocity, const std::string& texture_path);
    Zombie(const Zombie& rhs);
    ~Zombie() = default;

    void draw(sf::RenderTarget& target);

    void updatePosition(const myVec& playerPos);
    void updateSprite(int animation) const;
    friend std::ostream& operator<<(std::ostream& os, const Zombie& zombie);
    Zombie& operator=(const Zombie& zombie);
};
