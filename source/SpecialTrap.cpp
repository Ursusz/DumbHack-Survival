#include "../header/SpecialTrap.h"

SpecialTrap::SpecialTrap(const myVec &position, const std::string &texture_path, bool hitAble, bool collidable, bool isDynamic, int drawPriority, const std::string &sound_buffer_path)
    : Trap(position, texture_path, hitAble, collidable, isDynamic, drawPriority) {
    soundBuffer.loadFromFile(sound_buffer_path);
    sound.setBuffer(soundBuffer);
    sound.setVolume(40);
}

bool SpecialTrap::canHit(int frame) {
    if (frame > 600) {
        return true;
    }
    return false;
}

void SpecialTrap::takeDamage(int) {}

void SpecialTrap::interactWith(Entity &other, int frame) {
    if(auto playerptr = dynamic_cast<Player*> (&other)) {
        if(this->canHit(frame) && isSet) {
            playerptr->takeDamage(damage);
            isSet = false;
            sound.play();
            stopCollission();
        }
    }
}

SpecialTrap& SpecialTrap::operator=(const SpecialTrap &other) {
    if(this != &other) {
        Trap::operator=(other);
        soundBuffer = other.soundBuffer;
        sound.setBuffer(soundBuffer);
        sound.setVolume(40);
    }
    return *this;
}