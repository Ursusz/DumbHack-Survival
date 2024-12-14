#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>
#include <random>
#include <functional>

#include "../header/myVec.h"
#include "../header/Zombie.h"
#include "../header/Player.h"

class ZombieWaveManager {
    int currentWave;
    int zombiesPerWave;
    int spawnedZombies;
    int killedZombies;
    std::vector<std::shared_ptr<Zombie>> zombies;
public:
    ZombieWaveManager();

    void startNextWave();
    void spawnZombies();
    void updateZombies(Player& player, std::function<void(Entity&, Entity&)> collissionFunc);
    bool isWaveFinished() const;

    void drawZombies(sf::RenderTarget& target);

    void updateZombiesAnimations();

    void damageZombies(Player& player, int frame);

    const std::vector<std::shared_ptr<Zombie>>& getZombies() const;
};
