#include "../header/ZombieWaveManager.h"

ObstacleManager& ZombieWaveManager::obstacle_manager = ObstacleManager::getInstance();

ZombieWaveManager::ZombieWaveManager()
    : currentWave(0)
    , zombiesPerWave(2)
    , spawnedZombies(0)
    , killedZombies(0)
    , scoreText("Fonts/ARIAL.TTF",
                "Score: " + std::to_string(score),
                24,
                sf::Color::White,
                myVec(100, 456)){
    obstacle_manager.loadObstaclesWithBuffer("Init/world.txt", 23, 40);
}

void ZombieWaveManager::startNextWave() {
    currentWave++;
    killedZombies = 0;
    zombiesPerWave = 2 + currentWave;
    spawnedZombies = 0;
    killedZombies = 0;
    zombies.clear();
}

void ZombieWaveManager::spawnZombies() {
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_real_distribution<float> uniform_distX(72, 1848);
    std::uniform_real_distribution<float> uniform_distY(72, 1008);
    while(spawnedZombies < zombiesPerWave) {
        float spawnPosX = uniform_distX(rng);
        float spawnPosY = uniform_distY(rng);
        auto zombie = zombieBuilder.setPosition(myVec(spawnPosX, spawnPosY))
                                                    .setVelocity(myVec(2, 2))
                                                    .setTexturePath("assets/Zombie.png")
                                                    .setHitable(true)
                                                    .setCollidable(true)
                                                    .setIsDynamic(true)
                                                    .setDrawPriority(3)
                                                    .build();
        zombies.push_back(zombie);
        zombie->setObstacles(obstacle_manager.getObstacles());
        spawnedZombies++;
    }
}

void ZombieWaveManager::updateZombies(Player& player, std::function<void(Entity&, Entity&)> collissionFunc) {
    for(auto& zombie : zombies) {
        zombie->followPlayer(player.getPositionFromComp());
        collissionFunc(player, *zombie);
    }
    for(auto& zombie : zombies) {
        if(zombie->is_alive()) {
            zombie->updateSprite(zombie->getDirection());
        }else {
            killedZombies++;
            score += 50;
            scoreText.setString("Score: " + std::to_string(score));
        }
    }
    zombies.erase(std::remove_if(zombies.begin(), zombies.end(),
             [](std::shared_ptr<Zombie> z) { return !z->is_alive(); }),
             zombies.end());
}

bool ZombieWaveManager::isWaveFinished() const {
    return killedZombies >= zombiesPerWave;
}

void ZombieWaveManager::drawZombies(sf::RenderTarget& target) {
    for(auto& zombie : zombies) {
        zombie->draw(target);
        zombie->drawHP(target);
    }
    scoreText.drawText(target);
}

void ZombieWaveManager::updateZombiesAnimations() {
    for(auto& zombie : zombies) {
        zombie->changeAnimation();
    }
}

void ZombieWaveManager::damageZombies(Player &player, int frame) {
    for(auto& zombie : zombies) {
        myVec attackDirection(sf::Mouse::getPosition().x - player.getPositionFromComp().getX(), sf::Mouse::getPosition().y - player.getPositionFromComp().getY());
        try {
            attackDirection.normalize();
        }catch(const divideByZero& err) {
            std::cerr << "Division error: " << err.what() << std::endl;
        }
        if(player.isEnemyInFront(zombie->getPositionFromComp(), attackDirection, 110, 45)) {
            player.interactWith(*zombie, frame);
        }
    }
}

const std::vector<std::shared_ptr<Zombie>>& ZombieWaveManager::getZombies() const {
    return zombies;
}


