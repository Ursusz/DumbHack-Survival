#include "../header/Tile.h"

#include <SFML/Graphics/RenderTarget.hpp>

Tile::Tile(const myVec &position, const std::string& texture_path, const std::string& entity_type)
    : Entity(position, myVec(0, 0), texture_path, entity_type)
{}

void Tile::takeDamage(int /*damage*/) {}

bool Tile::canHit(int /*frame*/) {return false;}

std::shared_ptr<Entity> Tile::clone() const {
    return std::make_shared<Tile>(*this);
}

std::ostream &operator<<(std::ostream &os, const Tile &tile) {
    os << static_cast<const Entity&>(tile);
    return os;
}