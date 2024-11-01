#pragma once
#include <map>
#include <memory>

#include "../header/Components.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Player {
    std::shared_ptr<MotionComponent> m_cMotion;
    std::shared_ptr<KeyboardComponent> m_cKeyboard;
    std::shared_ptr<SpriteComponent> m_cSprite;
public:
    Player() = default;
    Player(const myVec& position, const myVec& velocity, const std::string& texture_path);
    Player(const Player& rhs);
    ~Player() = default;

    myVec getVelocityFromComp() const;
    myVec getPositionFromComp() const;
    void updatePositionInComp(const myVec& position) const;

    bool isKeyUp() const;
    bool isKeyDown() const;
    bool isKeyLeft() const;
    bool isKeyRight() const;

    void updateSprite(const std::string& direction, int animation) const;

    void setKeyValue(int, bool); /// 0 - Up, 1 - Down, 2 - Left, 3 - Right

    void draw(sf::RenderTarget& target);

    friend std::ostream& operator<<(std::ostream& os, const Player& player);
    Player& operator=(const Player& rhs);
};
