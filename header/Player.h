#pragma once

#include <utility>
#include <map>
#include <memory>
#include <math.h>
#include <array>

#include "../header/Components.h"
#include "../header/Entity.h"
#include "../header/Weapon.h"
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
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

class Player : public Entity{
    std::shared_ptr<KeyboardComponent> m_cKeyboard;
    sf::Sprite drawingSprite;
    std::shared_ptr<SpriteComponent> heartSprite;
    int hitPoints = 100;
    std::array<sf::Sprite, 5> hearts = {};
    int lastHit = 0;
    std::shared_ptr<Weapon> m_weapon;
    bool lastDirection = false;
    sf::VertexArray semicircle = sf::VertexArray(sf::TrianglesFan);
    bool canHit(int frame) override;
    int hitCooldown = 30;
    int player_damage = 15;

    sf::SoundBuffer swingBuffer;
    sf::Sound swingSound;
    sf::SoundBuffer unlockSoundBuffer;
    sf::Sound unlockSound;

    Text unlockPower;
    sf::Clock unlockPowerClock;
    void drawHP(sf::RenderTarget& m_window);

    void drawWeapon(sf::RenderTarget& m_window);

    void drawRange(sf::RenderTarget& target, float radius, float directionAngle);
public:
    Player() = default;
    Player(const myVec& position, const myVec& velocity, const std::string& texture_path, bool hitAble, bool collidable, bool isDynamic, int drawPriority);
    Player(const Player& rhs);
    ~Player() override = default;

    void reset() override;
    int getHP() const;

    bool isKeyUp() const;
    bool isKeyDown() const;
    bool isKeyLeft() const;
    bool isKeyRight() const;
    bool isAlive() const;

    void takeDamage(int damage) override;

    void interactWith(Entity &other, int frame) override;

    bool isEnemyInFront(const myVec& enemyPos, const myVec& playerDirection, float range, float  );

    void setKeyValue(int, bool); /// 0 - Up, 1 - Down, 2 - Left, 3 - Right

    void draw(sf::RenderTarget &target) override;

    void swap(Player &p1, Player &p2);
    std::shared_ptr<Entity> clone() const override;
    Player& operator=(Player rhs);
    friend std::ostream& operator<<(std::ostream& os, const Player& player);

    void takeBonus(int bonus, const std::string& option);
};
