#pragma once

#include "../header/Entity.h"
#include "../header/Components.h"

class Zombie : public Entity{
    sf::Sprite drawingSprite;
    std::string m_direction;    //this is the string that sets the zombie to look at a direction
    myVec direction;    //this is the direction vector
    int lastHit=0;
public:
    Zombie() = default;
    Zombie(const myVec& position, const myVec& velocity, const std::string& texture_path);
    Zombie(const Zombie& rhs);
    ~Zombie() override= default;

    std::string& getDirection();

    void updateHitCooldown(int frame) override;
    int getLastHit() const override;
    void followPlayer(const myVec& playerPos);
    Zombie& operator=(const Zombie& zombie);
};
