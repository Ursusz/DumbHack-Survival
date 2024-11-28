#pragma once

#include "../header/myVec.h"
#include "../header/Components.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
class Computer {
    const myVec position;
    std::shared_ptr<SpriteComponent> loadBarSprite;
    std::array<sf::Sprite, 12> loadBars;
    int frameCounterInsideComputerRange = 0;
    static int computersCount;
    bool hasCompleted = false;
public:
    Computer() = default;
    explicit Computer(const myVec& position);
    explicit Computer(const Computer& rhs);
    ~Computer();

    void drawLoadBars(sf::RenderTarget& target, const myVec& playerPos);
    static bool allComputersCompleted();
};