#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <array>
#include "../header/myVec.h"
#include "../header/Components.h"

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
    Computer(const Computer& rhs);
    ~Computer();

    void drawLoadBars(sf::RenderTarget& target, const myVec& playerPos);
    static bool allComputersCompleted();
};