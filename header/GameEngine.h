#pragma once

#include <fstream>
#include <iostream>
#include <unordered_set>

#include "../header/Computer.h"
#include "../header/Zombie.h"
#include "../header/Player.h"
#include "../header/TileManager.h"
#include "../header/Text.h"
#include "../header/Collision.h"
#include "../header/MapConfig.h"
#include "../header/VendingMachine.h"
#include "../header/Treasure.h"
#include "../header/ZombieWaveManager.h"
#include "../header/Trap.h"

/*
 ####################################################################
 #     X11 library on Linux has a defined macro named Status too    #
 #    and it collides with Status from sf::Audio::SoundSource.hpp   #
 #   so it must be undefined before including sfml audio libraries  #
 ####################################################################
 */
// #ifdef Status
// #undef Status
// #endif

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

class GameEngine {
    struct WindowSetup {int width=1920, height=1080, FPS=60; bool fullscreen=false;} myWindowConfig;
    struct PlayerSetup {float posX=0, posY=0, vecX=0, vecY=0; } myPlayerConfig;
    struct ZombieSetup {float posX=0, posY=0, vecX=0, vecY=0; } myZombieConfig;

    float newWidth = 0, newHeight = 0, windowAspectRatio = 0, mapAspectRatio = 0;

    Collision m_collision;

    sf::RenderWindow m_window;
    sf::VideoMode m_desktopMode;
    sf::View m_view;

    Text m_gameLostMsg;
    Text m_gameWonMsg;

    VendingMachine m_vending_machine;
    Player m_player;
    Zombie m_zombie;
    std::vector<Zombie> m_zombies;
    ZombieWaveManager m_zombieWaveManager;
    TileManager m_tileManager;

    Treasure* m_treasure = nullptr;

    std::map<sf::Keyboard::Key, int> keyMap;
    std::string m_setupPath;

    int m_frame = 0;
    std::vector<Computer> objectComputers;

    sf::Music m_music;

    Trap m_trap;

    void Init(const std::string& setupPath);

    void listenEvents();
    void handleEvents() const;
    void checkPlayerOutOfBounds();
    void loadingBarComputer();
    bool entitiesAreColliding(const Entity& e1, const Entity& e2) const;
public:
    void checkCollisions(Entity& e1, Entity& e2);
    explicit GameEngine(std::string  setupPath);
    ~GameEngine() = default;

    void run();

    friend std::ostream& operator << (std::ostream& os, const GameEngine& game) {
        os << "Setup path: " << game.m_setupPath << std::endl;
        return os;
    }
};
