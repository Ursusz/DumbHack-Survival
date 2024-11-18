#pragma once

#include "../header/Entity.h"
#include "../header/Components.h"
#include "../header/MapConfig.h"
#include "AStar.h"
#include <fstream>
#include <SFML/Graphics/RenderTarget.hpp>

class Zombie : public Entity{
    sf::Sprite drawingSprite;
    std::string m_direction;    //this is the string that sets the zombie to look at a direction
    myVec direction;    //this is the direction vector
    int lastHit=0;
    AStar::Generator m_generator;
    int next = 2;
    int obstacleReader = 0;
    int map[23][40];
public:
    Zombie() = default;
    Zombie(const myVec& position, const myVec& velocity, const std::string& texture_path, const std::string& entity_type);
    Zombie(const Zombie& rhs);
    ~Zombie() override = default;

    std::string& getDirection();

    void updateHitCooldown(int frame) override;
    int getLastHit() const override;
    void followPlayer(const myVec& playerPos);
    Zombie& operator=(const Zombie& zombie);
};
