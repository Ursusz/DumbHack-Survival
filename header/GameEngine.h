#pragma once

#include <fstream>
#include <iostream>
#include <unordered_set>

#include "../header/Text.h"
#include "../header/MapConfig.h"
#include "../header/EntityManager.h"

/*
 ####################################################################
 #     X11 library on Linux has a defined macro named Status too    #
 #    and it collides with Status from sf::Audio::SoundSource.hpp   #
 #   so it must be undefined before including sfml audio libraries  #
 ####################################################################
 */
#ifdef Status
#undef Status
#endif

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

class GameEngine {
    struct WindowSetup {int width=1920, height=1080, FPS=60; bool fullscreen=false;} myWindowConfig;

    float newWidth = 0, newHeight = 0, windowAspectRatio = 0, mapAspectRatio = 0;

    EntityManager& entityManager = EntityManager::getInstance();

    sf::RenderWindow m_window;
    sf::VideoMode m_desktopMode;
    sf::View m_view;

    Text m_gameLostMsg;
    Text m_gameWonMsg;

    std::map<sf::Keyboard::Key, int> keyMap;
    std::string m_setupPath;

    int m_frame = 0;

    sf::Music m_music;

    void Init(const std::string& setupPath);

    void listenEvents();
public:
    explicit GameEngine(std::string  setupPath);
    ~GameEngine() = default;

    void run();

    friend std::ostream& operator << (std::ostream& os, const GameEngine& game) {
        os << "Setup path: " << game.m_setupPath << std::endl;
        return os;
    }
};
