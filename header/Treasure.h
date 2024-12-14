#pragma once

#include "../header/Entity.h"
#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>
#include <random>

class Treasure : public Entity {
    static Treasure* uniqueInstance;
    bool m_isAvailable;
    int hitPoints = 100;
    const int SPAWN_TIME = 10;

    Treasure(const myVec &position, const myVec &velocity, const std::string &texture_path,
                                bool hitAble, bool collidable, bool isDynamic, bool isAvailable);

    Treasure& operator = (const Treasure& rhs) = delete;

    Treasure(const Treasure& rhs) = delete;

    std::shared_ptr<Entity> clone() const override { return nullptr; }
    bool isAvailable = true;

    bool canHit(int) override;
    void takeDamage(int damage) override;
    bool is_available() const;

    static void deleteInstance();
public:
    static Treasure* instance(const myVec &position, const myVec &velocity, const std::string &texture_path,
                                bool hitAble, bool collidable, bool isDynamic, bool isAvailable = true);

    void draw(sf::RenderTarget& target, int frame);

    void interactWith(Entity& other, int frame) override;
};