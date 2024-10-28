#pragma once
#include <memory>

#include "../header/Components.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
class Player {
    std::shared_ptr<MotionComponent> m_cMotion;
    std::shared_ptr<KeyboardComponent> m_cKeyboard;
    std::shared_ptr<SpriteComponent> m_cSprite;

public:
    Player() = default;
    Player(const myVec& position, const myVec& velocity, const std::string& texture_path);
    Player(const Player& rhs);
    ~Player() = default;

    std::shared_ptr<MotionComponent> getMotionComponent() const;
    std::shared_ptr<KeyboardComponent> getKeyboardComponent() const;
    std::shared_ptr<SpriteComponent> getSpriteComponent() const;

    void draw(sf::RenderTarget& target);

    friend std::ostream& operator<<(std::ostream& os, const Player& player);
    Player& operator=(const Player& rhs);
};
