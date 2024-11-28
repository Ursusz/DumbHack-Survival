
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../header/myVec.h"

class Weapon {
    sf::Sprite m_sprite;
    sf::Texture m_texture;
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
