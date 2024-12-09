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
        const std::string &entity_type);

    explicit VendingMachine(const Entity &rhs);
    ~VendingMachine() override = default;

    int takeDose();

    void takeDamage(int damage) override;
    bool canHit(int) override;
    std::shared_ptr<Entity> clone() const override;
};
