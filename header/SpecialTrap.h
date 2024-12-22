#pragma once

#include "../header/Trap.h"
#include "../header/Player.h"

/*
 ####################################################################
 #     X11 library on Linux has a defined macro named Status too    #
 #    and it collides with Status from sf::Audio::SoundSource.hpp   #
 #   so it must be undefined before including sfml audio libraries  #
 ####################################################################
 */
#ifdef Status
#undef Status
#endif

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class SpecialTrap : public Trap{
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;
public:
    SpecialTrap() = default;
    SpecialTrap(const myVec& position, const std::string& texture_path, bool hitAble, bool collidable, bool isDynamic, int drawPriority, const std::string& sound_buffer_path);
    ~SpecialTrap() override = default;

    bool canHit(int /*frame*/) override;
    void takeDamage(int /*damage*/) override;
    void interactWith(Entity &other, int frame) override;

    SpecialTrap& operator=(const SpecialTrap& other);
};