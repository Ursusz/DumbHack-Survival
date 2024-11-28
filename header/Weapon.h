
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include "../header/myVec.h"

class Weapon {
    int animationDuration=30;
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    bool lastDirection = 0;
    sf::Clock clock;
    int currentStage = -1;
public:
    Weapon() = default;
    explicit Weapon(const std::string& texturePath);
    Weapon(const Weapon& rhs);
    void draw(sf::RenderTarget& target, const myVec& position, bool direction); /* 0 - RIGHT; 1 - LEFT */
    void swing();
    void updateAnim();
};
