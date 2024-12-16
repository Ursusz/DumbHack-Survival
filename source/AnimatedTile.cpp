#include "../header/AnimatedTile.h"

std::string AnimatedTile::thisTyleType = "joke";

AnimatedTile::AnimatedTile(const myVec &position, const std::string &texture_path, bool hitAble, bool collidable, bool isDynamic, int drawPriority, const std::string &musicFilePath)
    : Tile(position, texture_path, thisTyleType, hitAble, collidable, isDynamic, drawPriority) {
    if(!music.openFromFile(musicFilePath)) {
        throw std::runtime_error("Failed to load music");
    }
    music.setVolume(40.0f);
}

bool AnimatedTile::canHit(int) {
    return music.getStatus() != sf::Music::Status::Playing;
}

void AnimatedTile::takeDamage(int) {}

void AnimatedTile::interactWith(Entity &other, int frame) {
    if(dynamic_cast<Player*> (&other)) {
        if(canHit(frame)) {
            music.play();
        }
    }
}

AnimatedTile& AnimatedTile::operator=(const AnimatedTile &other) {
    if(this != &other) {
        Entity::operator=(other);
        if(!music.openFromFile("assets/Kiss.ogg")) {
            throw std::runtime_error("Failed to load music");
        }
        music.setVolume(40.0f);
        this->thisTyleType = other.thisTyleType;
    }
    return *this;
}