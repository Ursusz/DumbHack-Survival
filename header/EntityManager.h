#pragma once

#include <memory>
#include <vector>

#include "../header/Entity.h"
#include "../header/ZombieWaveManager.h"
#include "../header/CollissionManager.h"
#include "../header/RenderClass.h"
#include "../header/TileManager.h"
#include "../header/Player.h"
#include "../header/VendingMachine.h"
#include "../header/Treasure.h"
#include "../header/AnimatedTile.h"
#include "../header/Trap.h"

#include <SFML/Graphics/RenderTarget.hpp>

class EntityManager {
    static EntityManager* uniqueInstance;
    std::vector<std::unique_ptr<Entity>> entities;
    EntityManager() = default;
    EntityManager(const EntityManager&) = delete;
    EntityManager& operator=(const EntityManager& rhs) = delete;
    ~EntityManager();

    Player m_player;
    ZombieWaveManager zombieWaveManager;
    CollissionManager collisionManager;
    TileManager tileManager;
    RenderClass renderer;

    std::vector<Computer> objectComputers;

    void addEntity(std::unique_ptr<Entity> entity, bool isMainEntity);
public:
    void drawComputerLoadBars(sf::RenderTarget& target);
    static EntityManager* instance();
    void deleteInstance();
    void initEntities();
    void computeZombieWaves();
    void togglePlayerKey(int key, bool value);
    void checkPlayerOutOfBound(const sf::RenderWindow& m_window);
    void handlePlayerEvents();
    void attackZombies(int frame);
    void resetMainEntitiesForCollissions(int frame);
    void drawEntities(sf::RenderTarget& target, int frame);
    void updateAnimations();

    int verifyPlayerExistance_and_ComputersCompletion(sf::RenderTarget& target, int frame);
    bool isGameStillPlayable() const;
};
