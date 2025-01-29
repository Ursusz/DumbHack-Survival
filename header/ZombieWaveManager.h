#pragma once

#include <memory>
#include <vector>
#include <random>
#include <functional>
#include <fstream>

#include "../header/myVec.h"
#include "../header/Zombie.h"
#include "../header/Player.h"
#include "../header/ObstacleManager.h"
#include "../header/ZombieBuilder.h"
#include "../header/Text.h"

#include <SFML/Graphics/RenderTarget.hpp>

class ZombieWaveManager {
    int currentWave;
    int zombiesPerWave;
    int spawnedZombies;
    int killedZombies;
    std::vector<std::shared_ptr<Zombie>> zombies;
    static ObstacleManager& obstacle_manager;
    ZombieBuilder zombieBuilder;
    int score = 0;
    Text scoreText;
    Text highScoreText;
    std::fstream file;
    int highScore = 0;
public:
    ZombieWaveManager();
    ~ZombieWaveManager();

    void startNextWave();
    void spawnZombies();
    void updateZombies(Player& player, std::function<void(Entity&, Entity&)> collissionFunc);
    bool isWaveFinished() const;

    void drawZombies(sf::RenderTarget& target);

    void updateZombiesAnimations();

    void damageZombies(Player& player, int frame);

    const std::vector<std::shared_ptr<Zombie>>& getZombies() const;
};
