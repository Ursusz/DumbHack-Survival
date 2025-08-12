#include "../header/EntityManager.h"

EntityManager::~EntityManager() {
    entities.clear();
}

void EntityManager::addEntity(std::unique_ptr<Entity> entity, bool isMainEntity) {
    Entity* entityPtr = entity.get();
    entities.push_back(std::move(entity));
    if(isMainEntity) {
        collisionManager.add_main_entities(entityPtr);
    }else {
        collisionManager.add_entities_to_verify_collission(entityPtr);
    }
    renderer.addEntity(entityPtr);
}

void EntityManager::drawComputerLoadBars(sf::RenderTarget& target) {
    for(auto& computer : objectComputers) {
        computer.drawLoadBars(target, m_player.getPositionFromComp());
    }
}

void EntityManager::initEntities() {

    tileManager.loadMap("./Init/world.txt", objectComputers);
    for(size_t i = 0; i < MAP_HEIGHT; i++) {
        for(size_t j = 0; j < MAP_WIDTH; j++) {
            collisionManager.add_entities_to_verify_collission(&tileManager.getTile(i, j));
        }
    }
    /// 1889 552
    m_player = Player(myVec(1000, 552),
                        myVec(5, 5),
                        "assets/Player.png",
                        true,
                        true,
                        true,
                        2);
    collisionManager.add_main_entities(&m_player);
    renderer.addEntity(&m_player);

    addEntity(std::make_unique<VendingMachine>(myVec(984, 110),
                                                                myVec(0, 0),
                                                                "assets/vendingmachine.png",
                                                                false,
                                                                true,
                                                                false,
                                                                2),
                                                                false);

    addEntity(std::unique_ptr<Entity>(Treasure::instance(myVec(120, 552),
                                                                 myVec(0, 0),
                                                                 "assets/Treasure.png",
                                                                 true,
                                                                 true,
                                                                 false,
                                                                 true,
                                                                 2)),
                                                                 false);

    addEntity(std::make_unique<AnimatedTile>(myVec(1848, 452),
                                                            "assets/Treasure.png",
                                                            false,
                                                            true,
                                                            false,
                                                            2,
                                                            "assets/Kiss.ogg"),
                                                            false);

    addEntity(std::make_unique<SpecialTreasureRemastered>(myVec(1848, 656),
                                                            "assets/SpecialTreasureRemastered.png",
                                                            false,
                                                            true,
                                                            false,
                                                            2),
                                                            false);
    addEntity(std::make_unique<SpecialTrap>(myVec(1512, 216),
                                                             "assets/SpecialTrap.png",
                                                             false,
                                                             false,
                                                             false,
                                                             1,
                                                             "assets/SpecialTrapSound.ogg"),
                                                             false);
    addEntity(std::make_unique<Trap>(myVec(504, 792),
                                                    "assets/Trap.png",
                                                    false,
                                                    false,
                                                    false,
                                                    1),
                                                    false);
}

void EntityManager::resetEntities() {
    zombieWaveManager.resetZombies();
    for (auto& entity : entities) {
        entity->reset();
    }
    m_player.reset();
    for(auto& computer : objectComputers) {
        computer.reset();
    }
}

void EntityManager::computeZombieWaves() {
    if(zombieWaveManager.isWaveFinished()) {
        zombieWaveManager.startNextWave();
    }else {
        zombieWaveManager.spawnZombies();
    }
}

void EntityManager::togglePlayerKey(int key, bool value) {
    m_player.setKeyValue(key, value);
}

void EntityManager::checkPlayerOutOfBound(const sf::RenderWindow &m_window) {
    if(m_player.getPositionFromComp().getX() < 16)                          m_player.setPositionInComp(myVec(16, m_player.getPositionFromComp().getY()));
    if(m_player.getPositionFromComp().getX() > m_window.getSize().x - 16)   m_player.setPositionInComp(myVec(m_window.getSize().x - 16, m_player.getPositionFromComp().getY()));
    if(m_player.getPositionFromComp().getY() < 16)                          m_player.setPositionInComp(myVec(m_player.getPositionFromComp().getX(),16));
    if(m_player.getPositionFromComp().getY() > m_window.getSize().y - 16)   m_player.setPositionInComp(myVec(m_player.getPositionFromComp().getX(), m_window.getSize().y - 16));
}

void EntityManager::handlePlayerEvents() {
    myVec direction(0.0f, 0.0f);
    if(m_player.isKeyUp()) {
        direction += myVec(0, -m_player.getVelocityFromComp().getY());
        m_player.updateSprite("up");
    }
    if(m_player.isKeyDown()) {
        direction += myVec(0, m_player.getVelocityFromComp().getY());
        m_player.updateSprite("down");

    }
    if(m_player.isKeyLeft()) {
        direction += myVec(-m_player.getVelocityFromComp().getX(), 0);
        m_player.updateSprite("left");

    }
    if(m_player.isKeyRight()) {
        direction += myVec(m_player.getVelocityFromComp().getX(), 0);
        m_player.updateSprite("right");
    }

    if(direction.getX() != 0.0f && direction.getY() != 0.0f) {
        try {
            direction.normalize();
        }catch(const divideByZero& err) {
            std::cerr << "Division error: " << err.what() << std::endl;
        }
        direction *= 5.0f;
    }
    m_player.updatePositionInComp(direction);
}


void EntityManager::attackZombies(int frame) {
    zombieWaveManager.damageZombies(m_player, frame);
}

void EntityManager::resetMainEntitiesForCollissions(int frame) {
    collisionManager.clear_main_entities();
    collisionManager.add_main_entities(&m_player);

    for(auto& zombie : zombieWaveManager.getZombies()) {
        collisionManager.add_main_entities(zombie.get());
    }
    collisionManager.verifyAllCollissions(frame);
}

void EntityManager::drawEntities(sf::RenderTarget &target, int frame) {
    tileManager.printMap(target);
    renderer.drawAll(target, frame);
}

void EntityManager::updateAnimations() {
    m_player.changeAnimation();
    zombieWaveManager.updateZombiesAnimations();
}

int EntityManager::verifyPlayerExistance_and_ComputersCompletion(sf::RenderTarget& target, int frame) {
    drawComputerLoadBars(target);
    if(m_player.isAlive() && !Computer::allComputersCompleted()) {
        zombieWaveManager.updateZombies(m_player, [this, frame](Entity& e1, Entity& e2) {
            this->collisionManager.checkCollisions(e1, e2, frame);
        });
        zombieWaveManager.drawZombies(target);
    }else if(!m_player.isAlive()) {
        return 0;
    }else if(Computer::allComputersCompleted()) {
        return 1;
    }
    return 2;
}

bool EntityManager::isGameStillPlayable() const {
    return m_player.isAlive() && !Computer::allComputersCompleted();
}

Player& EntityManager::getPlayer() {
    return m_player;
}

const std::vector<std::shared_ptr<Zombie>>& EntityManager::getZombies() const {
    return zombieWaveManager.getZombies();
};

std::vector<std::pair<float, float>> EntityManager::getComputerPositions() const {
    std::vector<std::pair<float, float>> positions;
    for (const auto& computer : objectComputers) {
        positions.emplace_back(computer.getPosition().getX(), computer.getPosition().getY());
    }
    return positions;
};

std::vector<int> EntityManager::getComputersCompletions() const {
    std::vector<int> computers;
    for (const auto& computer : objectComputers) {
        computers.emplace_back(computer.getCompletion());
    }
    return computers;
}

std::vector<std::pair<float, float>> EntityManager::getTrapsPositions() const {
    std::vector<std::pair<float, float>> positions;
    for (const auto& entity : entities) {
        if (const Trap* trap = dynamic_cast<const Trap*>(entity.get())) {
            positions.emplace_back(trap->getPositionFromComp().getX(), trap->getPositionFromComp().getY());
        }else if (const SpecialTrap* trap1 = dynamic_cast<const SpecialTrap*>(entity.get())) {
            positions.emplace_back(trap1->getPositionFromComp().getX(), trap->getPositionFromComp().getY());
        }
    }
    return positions;
}