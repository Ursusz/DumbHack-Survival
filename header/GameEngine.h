#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "myVec.h"
#include "Player.h"


inline struct WindowSetup {int width, height, FPS; bool fullscreen;} myWindowConfig;

class GameEngine {
    sf::RenderWindow m_window;
    Player m_player;
    std::string m_setupPath;
    void Init(const std::string& setupPath);

    void listenEvents();
    void handleEvents();
public:
    explicit GameEngine(const std::string& setupPath);
    ~GameEngine() = default;

    void run();

    friend std::ostream& operator << (std::ostream& os, const GameEngine& game) {
        os << "Setup path: " << game.m_setupPath << std::endl;
        return os;
    }
};