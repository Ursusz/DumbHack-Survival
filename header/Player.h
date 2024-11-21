#pragma once
#include <map>
#include <memory>
#include <math.h>
#include "../header/Components.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../header/Entity.h"

class Player : public Entity{
    std::shared_ptr<KeyboardComponent> m_cKeyboard;
    sf::Sprite drawingSprite;
    std::shared_ptr<SpriteComponent> heartSprite;
    int hitPoints = 100;
    std::array<sf::Sprite, 5> hearts = {};
    int lastHit = 0;

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


    bool isEnemyInFront(const myVec& enemyPos, const myVec& playerDirection, float range, float angleThreshHold);

    void setKeyValue(int, bool); /// 0 - Up, 1 - Down, 2 - Left, 3 - Right

    void drawHP(sf::RenderTarget& m_window);
    bool isInComputerRange() const;

    Player& operator=(const Player& rhs);
};
