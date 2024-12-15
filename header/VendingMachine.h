#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Clock.hpp>
#include "../header/Entity.h"

class VendingMachine : public  Entity{
    int numOfDoses = 5;
    sf::Clock clock;
    float lastUsedTime = 0.0f;
    bool canHit(int) override;
public:
    VendingMachine() = default;

    VendingMachine(const myVec &position, const myVec &velocity, const std::string &texture_path,
                    bool hitAble, bool collidable, bool isDynamic);

    explicit VendingMachine(const Entity &rhs);
    ~VendingMachine() override = default;

    void takeDamage(int damage) override;
    void interactWith(Entity &other, int frame) override;
    std::shared_ptr<Entity> clone() const override;
};
