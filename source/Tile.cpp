#include "../header/Tile.h"

#include <SFML/Graphics/RenderTarget.hpp>

Tile::Tile(const myVec &position, const std::string& texture_path, std::string& tileType, bool hitAble, bool collidable, bool isDynamic, int drawPriority)
    : Entity(position, myVec(0, 0), texture_path, hitAble, collidable, isDynamic, drawPriority)
    , tileType(tileType)
{}

void Tile::takeDamage(int /*damage*/) {}

bool Tile::canHit(int /*frame*/) {return false;}

void Tile::interactWith(Entity & /*other*/, int /*frame*/) {}

std::shared_ptr<Entity> Tile::clone() const {
    return std::make_shared<Tile>(*this);
}

std::ostream &operator<<(std::ostream &os, const Tile &tile) {
    os << static_cast<const Entity&>(tile);
    return os;
}

void Tile::reset() {
}


Tile &Tile::operator=(const Tile &rhs) {
    Entity::operator=(rhs);
    std::swap(this->tileType, rhs.tileType);
    return *this;
}
