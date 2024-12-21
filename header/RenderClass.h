#pragma once

#include "../header/Entity.h"
#include "../header/Treasure.h"
#include "../header/Trap.h"

#include <vector>
#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>

class RenderClass {
    std::vector<Entity*> entities;
public:
    RenderClass() = default;
    ~RenderClass();
    void addEntity(Entity* entity);
    void drawAll(sf::RenderTarget& target, int frame);
};