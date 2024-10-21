#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "SFML/Graphics.hpp"

inline struct WindowSetup {int width, height, FPS; bool fullscreen;} myWindowConfig;

class GameEngine {
    sf::RenderWindow m_window;

    std::string m_setupPath;
    void Init(const std::string& setupPath);

public:
    explicit GameEngine(const std::string& setupPath);
    ~GameEngine() = default;

    void run();

    friend std::ostream& operator << (std::ostream& os, const GameEngine& game) {
        os << "Setup path: " << game.m_setupPath << std::endl;
        return os;
    }
};