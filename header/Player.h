#pragma once

#include <utility>
#include <map>
#include <memory>
#include <math.h>
#include "../header/Components.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <array>
#include "../header/Entity.h"
#include "../header/Weapon.h"

class Player : public Entity{
    std::shared_ptr<KeyboardComponent> m_cKeyboard;
    sf::Sprite drawingSprite;
    std::shared_ptr<SpriteComponent> heartSprite;
    int hitPoints = 100;
    std::array<sf::Sprite, 5> hearts = {};
    int lastHit = 0;
    std::shared_ptr<Weapon> m_weapon;
    bool lastDirection = false;
    sf::VertexArray semicircle = sf::VertexArray(sf::TrianglesFan);
public:
    Player() = default;
    Player(const myVec& position, const myVec& velocity, const std::string& texture_path, const std::string& entity_type);
    Player(const Player& rhs);
    ~Player() override = default;

    bool isKeyUp() const;
    bool isKeyDown() const;
    bool isKeyLeft() const;
    bool isKeyRight() const;
    bool isAlive() const;

    void takeDamage(int damage) override;
    bool canHit(int frame) override;

    bool isEnemyInFront(const myVec& enemyPos, const myVec& playerDirection, float range, float  );

    void setKeyValue(int, bool); /// 0 - Up, 1 - Down, 2 - Left, 3 - Right

    void drawHP(sf::RenderTarget& m_window);

    void drawWeapon(sf::RenderTarget& m_window);
    void swingWeapon();

    void drawRange(sf::RenderTarget& target, float radius, float directionAngle);

    void swap(Player &p1, Player &p2);
    std::shared_ptr<Entity> clone() const override;
    Player& operator=(Player rhs);
};
