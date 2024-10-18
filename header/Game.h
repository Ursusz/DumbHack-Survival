#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <fstream>

inline struct WindowConfig{int width, height, FPS; bool fullScreen; } m_windowConfig;

class Game {
    sf::RenderWindow m_window;
    std::string m_keyToken;

    void init(const std::string& path);
    void spawnPlayer();
public:
    Game(const std::string& path) {
        init(path);
    };
    void run();
};