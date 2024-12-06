#pragma once
#include "../header/myVec.h"
#include "../header/Exceptions.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <memory>

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

    void setPosition(const myVec& position) {
        m_position = position;
    }

    std::shared_ptr<MotionComponent> clone() {
        return std::make_shared<MotionComponent>(*this);
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

    std::shared_ptr<KeyboardComponent> clone() {
        return std::make_shared<KeyboardComponent>(*this);
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
        if(!m_texture.loadFromFile(texture_path))
            throw textureError(texture_path);
        m_sprite.setTexture(m_texture);
        m_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
        m_sprite.setScale(3.0f, 3.0f);
    }

    void updateSpriteComponent(const std::string& direction, int animation) {
        //16 means the size in X and Y of my sprite;
        //player.png is 48x32 containing 6 different frames for each direction
        //0, 17 and 33 are the position on X axes in Player.png where the texture for each direction is located
        //animation variable is the same, but on Y axes and it is changed every 12 frames to create a walking effect
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

    std::shared_ptr<SpriteComponent> clone() const {
        auto clonedComponent = std::make_shared<SpriteComponent>();
        clonedComponent->m_texturePath = m_texturePath;

        if (!clonedComponent->m_texture.loadFromFile(m_texturePath)) {
            throw textureError(m_texturePath);
        }

        clonedComponent->m_sprite = m_sprite;
        clonedComponent->m_sprite.setTexture(clonedComponent->m_texture);

        return clonedComponent;
    }

    sf::Sprite getSprite() const {
        return m_sprite;
    }
};

class BoundingBoxComponent {
    int m_halfWidth=0;
    int m_halfHeight=0;
public:
    BoundingBoxComponent() = default;
    BoundingBoxComponent(int halfWidth, int halfHeight) : m_halfWidth(halfWidth), m_halfHeight(halfHeight) {}
    ~BoundingBoxComponent() = default;
    int getHalfWidth() const {
        return m_halfWidth;
    }
    int getHalfHeight() const {
        return m_halfHeight;
    }

    std::shared_ptr<BoundingBoxComponent> clone() {
        return std::make_shared<BoundingBoxComponent>(m_halfWidth, m_halfHeight);
    }
};