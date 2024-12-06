#pragma once

#include <memory>

#include "../header/Components.h"
#include "../header/Entity.h"
#include "../header/myVec.h"

class Tile : public Entity{
public:
    Tile() = default;
    Tile(const myVec& position, const std::string& texture_path, const std::string& entity_type);
    ~Tile() override = default;

    void takeDamage(int damage) override;
    bool canHit(int) override;
};