#include "../header/Weapon.h"

Weapon::Weapon(const std::string &texturePath) {
    if(!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load sprite texture: " << texturePath << std::endl;
    }
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    m_sprite.setScale(1.0f, 1.0f);
}

Weapon::Weapon(const Weapon &rhs)
    : m_sprite(rhs.m_sprite)
    , m_texture(rhs.m_texture)
{}


void Weapon::draw(sf::RenderTarget &target, const myVec& position, bool direction) {
    ///sclae variable is rescaling the original texture from 16x16 to 32x32, and also it's mirroring the texture if
    ///the player is moving left or right by multiplying the x scale with -1
    const float scale = direction ? -2.0f : 2.0f;
    m_sprite.setOrigin(8, 8);
    ///scale*12 is added to position because the player sprite is 48x48, and the weapon should be at player's edge
    ///center of the player +- 24px depending on the direction
    m_sprite.setPosition(position.getX() + scale*12, position.getY());
    m_sprite.setScale(scale, 2);
    target.draw(m_sprite);
}

void Weapon::swing() {
    currentStage = 0;
    clock.restart();
}

void Weapon::updateAnim() {
    if(currentStage != -1) {
        ///the frame for weapon animation is changed every 0.15 seconds
        if(clock.getElapsedTime().asSeconds() >= 0.15) {
            currentStage ++;
            if(currentStage > 2) {
                m_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
            }else {
                m_sprite.setTextureRect(sf::IntRect(currentStage*16, 0, 16, 16));
                clock.restart();
            }
        }
    }
}

