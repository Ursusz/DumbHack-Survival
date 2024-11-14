#pragma once
#include <map>
#include <memory>

#include "../header/Components.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../header/Entity.h"

class Player : public Entity{
    std::shared_ptr<KeyboardComponent> m_cKeyboard;
    sf::Sprite drawingSprite;
    int hitPoints = 100;

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

    void updateHitPoints(int damage) override;
    int getHitPoints() const override;

    void setKeyValue(int, bool); /// 0 - Up, 1 - Down, 2 - Left, 3 - Right

    Player& operator=(const Player& rhs);
};
