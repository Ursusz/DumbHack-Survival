#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "../header/Entity.h"
#include <SFML/System/Clock.hpp>

class VendingMachine : public  Entity{
    int numOfDoses = 5;
    sf::Clock clock;
    float lastUsedTime = 0.0f;
public:
    VendingMachine() = default;

    VendingMachine(const myVec &position, const myVec &velocity, const std::string &texture_path,
                    bool hitAble, bool collidable, bool isDynamic);

    explicit VendingMachine(const Entity &rhs);
    ~VendingMachine() override = default;

    void takeDamage(int damage) override;
    bool canHit(int) override;
    void interactWith(Entity &other, int frame) override;
    std::shared_ptr<Entity> clone() const override;
};
