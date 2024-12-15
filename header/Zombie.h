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
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

class Zombie : public Entity{
    std::shared_ptr<SpriteComponent> heartSprite;
    std::array<sf::Sprite, 5> hearts = {};
    sf::Sprite drawingSprite;
    std::string m_direction;    //this is the string that sets the zombie to look at a direction
    myVec direction;    //this is the direction vector where the zombie is heading
    int lastHit=0;
    AStar::Generator m_generator;
    int next = 2;   ///next is the index of the next cell in which the zombie should go in the list generated by path finder
    int obstacleReader = 0;
    int hitPoints = 100;
    bool isAlive = true;

    std::shared_ptr<sf::SoundBuffer> hitBuffer;
    sf::Sound hitSound;

    bool canHit(int) override;
public:
    Zombie() = default;
    Zombie(const myVec& position, const myVec& velocity, const std::string& texture_path, bool hitAble, bool collidable, bool isDynamic);
    Zombie(const Zombie& rhs);
    ~Zombie() override = default;

    std::string& getDirection();

    void takeDamage(int damage) override;
    void interactWith(Entity &other, int frame) override;

    void drawHP(sf::RenderTarget& m_window);

    void followPlayer(const myVec& playerPos);

    bool is_alive() const;

    std::shared_ptr<Entity> clone() const override;

    void swap(Zombie& z1, Zombie& z2) noexcept;
    Zombie& operator=(Zombie zombie);

    friend std::ostream& operator<<(std::ostream& os, const Zombie& zombie);
};