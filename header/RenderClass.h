#pragma once

#include "../header/Entity.h"

#include <vector>
#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>

class RenderClass {
    std::vector<Entity*> entities;
public:
    void addEntity(Entity* entity);
    void drawAll(sf::RenderTarget& target);
};