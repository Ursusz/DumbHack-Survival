#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Zombie.h"
#include "../header/myVec.h"
#include "../header/Player.h"
#include "../header/TileManager.h"

class GameEngine {
    struct WindowSetup {int width=720, height=480, FPS=60; bool fullscreen=false;} myWindowConfig;
    struct PlayerSetup {float posX=0, posY=0, vecX=0, vecY=0; } myPlayerConfig;
    struct ZombieSetup {float posX=0, posY=0, vecX=0, vecY=0; } myZombieConfig;

    float newWidth = 0, newHeight = 0, windowAspectRatio = 0, mapAspectRatio = 0;
    float deltaX=0, deltaY=0;
    float overlapX=0, overlapY=0;
    sf::RenderWindow m_window;
    sf::VideoMode m_desktopMode;
    sf::View m_view;
    sf::Text m_text;
    sf::Text gameState;
    sf::Font m_font;
    Player m_player;
    Zombie m_zombie;
    TileManager m_tileManager;

    std::map<sf::Keyboard::Key, int> keyMap;
    std::string m_setupPath;
    int m_frame=0;
    int m_playerFrameCounter = 0;
    int m_animationPlayer = 0;
    int m_zombieFrameCounter = 0;
    int m_animationZombie = 0;

    void Init(const std::string& setupPath);

    void listenEvents();
    void handleEvents() const;
    void checkPlayerOutOfBounds();
    void checkCollisions(Entity& p, Entity& z);
public:
    explicit GameEngine(std::string  setupPath);
    ~GameEngine() = default;

    void run();

    friend std::ostream& operator << (std::ostream& os, const GameEngine& game) {
        os << "Setup path: " << game.m_setupPath << std::endl;
        return os;
    }
};
