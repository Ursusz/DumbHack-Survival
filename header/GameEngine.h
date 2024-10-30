#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Zombie.h"
#include "../header/myVec.h"
#include "../header/Player.h"
#include "../header/Tile.h""


inline struct WindowSetup {int width, height, FPS; bool fullscreen;} myWindowConfig;

class GameEngine {
    sf::RenderWindow m_window;
    Player m_player;
    Zombie m_zombie;
    std::string m_setupPath;
    int m_frame = 0;
    int m_animation = 0;
    sf::RectangleShape rect;
    sf::RectangleShape rect2;
    Tile m_tile[40][23];


    void Init(const std::string& setupPath);

    void listenEvents();
    void handleEvents();
public:
    explicit GameEngine(std::string  setupPath);
    ~GameEngine() = default;

    void run();

    friend std::ostream& operator << (std::ostream& os, const GameEngine& game) {
        os << "Setup path: " << game.m_setupPath << std::endl;
        return os;
    }
};
