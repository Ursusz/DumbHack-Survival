#pragma once

#include "../header/Entity.h"
#include "../header/Components.h"
#include "../header/MapConfig.h"
#include <AStar.h>
#include <fstream>
#include <SFML/Graphics/RenderTarget.hpp>
#include <math.h>
#include <array>
#include <memory>

class Zombie : public Entity{
    std::shared_ptr<SpriteComponent> heartSprite;
    std::array<sf::Sprite, 5> hearts = {};
    sf::Sprite drawingSprite;
    std::string m_direction;    //this is the string that sets the zombie to look at a direction
    myVec direction;    //this is the direction vector where the zombie is heading
    int lastHit=0;
    AStar::Generator m_generator;
    int next = 2;
    int obstacleReader = 0;
    int hitPoints = 100;
    bool isAlive = true;
public:
    Zombie() = default;
    Zombie(const myVec& position, const myVec& velocity, const std::string& texture_path, const std::string& entity_type);
    Zombie(const Zombie& rhs);
    ~Zombie() override = default;

    std::string& getDirection();

    void takeDamage(int damage) override;
    bool canHit(int) override;

    void drawHP(sf::RenderTarget& m_window);

    void followPlayer(const myVec& playerPos);

    std::shared_ptr<Entity> clone() const override;

    void swap(Zombie& z1, Zombie& z2);
    Zombie& operator=(Zombie zombie);

    friend std::ostream& operator<<(std::ostream& os, const Zombie& zombie);
};