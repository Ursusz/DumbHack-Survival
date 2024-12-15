#pragma once

#include "../header/Entity.h"
#include "../header/Text.h"

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

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class VendingMachine : public  Entity{
    int numOfDoses = 5;
    sf::Clock clock;
    float lastUsedTime = 0.0f;
    bool canHit(int) override;
    Text dosesLeft;
    Text leftTimeToNextDose;
    sf::SoundBuffer drinkBuffer;
    sf::Sound drinkSound;
public:
    VendingMachine() = default;

    VendingMachine(const myVec &position, const myVec &velocity, const std::string &texture_path,
                    bool hitAble, bool collidable, bool isDynamic);

    explicit VendingMachine(const Entity &rhs);
    ~VendingMachine() override = default;

    void drawTexts(sf::RenderTarget& target);

    void takeDamage(int damage) override;
    void interactWith(Entity &other, int frame) override;
    std::shared_ptr<Entity> clone() const override;
    VendingMachine& operator=(const VendingMachine &rhs);
};
