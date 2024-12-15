#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>
#include <random>
#include "../header/Entity.h"

class Treasure : public Entity {
    static Treasure* uniqueInstance;
    bool m_isAvailable;
    int hitPoints = 100;
    const int SPAWN_TIME = 10;

    Treasure(const myVec &position, const myVec &velocity, const std::string &texture_path,
                                bool hitAble, bool collidable, bool isDynamic, bool isAvailable);

    Treasure& operator = (const Treasure& rhs) = delete;

    Treasure(const Treasure& rhs) = delete;

    ~Treasure() override;

    std::shared_ptr<Entity> clone() const override { return nullptr; }

    bool canHit(int) override;
    void takeDamage(int damage) override;

public:
    static void deleteInstance();
    bool is_available() const;
    static Treasure* instance(const myVec &position, const myVec &velocity, const std::string &texture_path,
                                bool hitAble, bool collidable, bool isDynamic, bool isAvailable = true);

    void draw(sf::RenderTarget& target, int frame);

    void interactWith(Entity& other, int frame) override;

    static bool hasInstance();
};