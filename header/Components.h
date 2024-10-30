#pragma once
#include "../header/myVec.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class MotionComponent {
    myVec m_position = {0.0f, 0.0f};
    myVec m_velocity = {0.0f, 0.0f};
public:
    MotionComponent() = default;
    MotionComponent(const myVec& position, const myVec& velocity)
        : m_position(position)
        , m_velocity(velocity)
    {}
    ~MotionComponent() = default;

    myVec getPosition() const {
        return m_position;
    }

    myVec getVelocity() const {
        return m_velocity;
    }

    friend std::ostream& operator << (std::ostream& os, const MotionComponent& m) {
        os << "Position: " << m.m_position << " Velocity: " << m.m_velocity;
        return os;
    }

    void updatePosition(const myVec& direction) {
        m_position += direction;
    }

    /// Maybe used later
    /*
    void updateVelocity(const myVec& velocity) {
        m_velocity = velocity;
    }*/
};

class KeyboardComponent {
    bool isUp = false;
    bool isDown = false;
    bool isLeft = false;
    bool isRight = false;
public:
    KeyboardComponent() = default;
    bool up() const {
        return isUp;
    }
    bool down() const {
        return isDown;
    }
    bool left() const {
        return isLeft;
    }
    bool right() const {
        return isRight;
    }

    void setUp(bool value) {
        isUp = value;
    }
    void setDown(bool value) {
        isDown = value;
    }
    void setLeft(bool value) {
        isLeft = value;
    }
    void setRight(bool value) {
        isRight = value;
    }
    friend std::ostream& operator << (std::ostream& os, const KeyboardComponent& k) {
        os << k.isUp << " " << k.isDown << " " << k.isLeft << " " << k.isRight;
        return os;
    }
};

class SpriteComponent {
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    std::string m_texturePath;
public:
    SpriteComponent() = default;

    explicit SpriteComponent(const std::string& texture_path)
        :m_texturePath(texture_path)
    {
        if(!m_texture.loadFromFile(texture_path)) {
            std::cerr << "Failed to load sprite texture: " << texture_path << std::endl;
        }
        m_sprite.setTexture(m_texture);
        m_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
        m_sprite.setScale(3.0f, 3.0f);
    }

    void updateSpriteComponent(const std::string& direction, int animation) {
        sf::IntRect textureRect;
        if(direction == "up") {
            textureRect = sf::IntRect(33, animation, 16, 16);
            m_sprite.setTextureRect(textureRect);
            m_sprite.setScale(3.0f, 3.0f);
        }
        if(direction == "down") {
            textureRect = sf::IntRect(17, animation, 16, 16);
            m_sprite.setTextureRect(textureRect);
            m_sprite.setScale(3.0f, 3.0f);

        }
        if(direction == "left") {
            textureRect = sf::IntRect(0, animation, 16, 16);
            m_sprite.setTextureRect(textureRect);
            m_sprite.setScale(-3.0f, 3.0f);
        }
        if(direction == "right") {
            textureRect = sf::IntRect(0, animation, 16, 16);
            m_sprite.setTextureRect(textureRect);
            m_sprite.setScale(3.0f, 3.0f);
        }
    }


    sf::Sprite getSprite() const {
        return m_sprite;
    }

    ///Maybe used later
    // void setSprite(const sf::Texture& texture) {
    //     m_sprite.setTexture(texture);
    // }
};