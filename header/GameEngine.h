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
    GameEngine(const std::string& setupPath);


    void run();
};