#include "../header/Zombie.h"
#include <SFML/Graphics/RenderTarget.hpp>

Zombie::Zombie(const myVec &position, const myVec &velocity, const std::string &texture_path, const std::string& entity_type)
    : Entity(position, velocity, texture_path, entity_type) {
    m_generator.setWorldSize({23, 40});
    m_generator.setHeuristic(AStar::Heuristic::euclidean);
    m_generator.setDiagonalMovement(true);
}

Zombie::Zombie(const Zombie& rhs)
    : Entity(rhs)
    , m_generator(rhs.m_generator)
{}

std::string &Zombie::getDirection() {
    return m_direction;
}

void Zombie::updateHitCooldown(int frame) {
    lastHit = frame;
}

int Zombie::getLastHit() const {
    return lastHit;
}

void Zombie::followPlayer(const myVec &playerPos) {
    if(this->getPositionFromComp().distance(playerPos) > 100) {
        auto path = m_generator.findPath({(int)playerPos.getY()/48, (int)playerPos.getX()/48},
                        {(int)this->getPositionFromComp().getY()/48, (int)this->getPositionFromComp().getX()/48});
        if(this->getPositionFromComp()/48 != playerPos/48 && (int)path.size() > next) {
            if(this->getPositionFromComp().getX()/48 < path.at(next).x || this->getPositionFromComp().getX()/48 > path.at(next).x
                    || this->getPositionFromComp().getY() < path.at(next).y || this->getPositionFromComp().getY()/48 > path.at(next).y) {
                direction = myVec(path.at(next).y * 48 + 24 - this->getPositionFromComp().getX(), path.at(next).x * 48 + 24 - this->getPositionFromComp().getY());
                    }else {
                        next++;
                    }
        }
    }else {
        direction = playerPos - this->getPositionFromComp();
    }
    ///Zombie width and height are both 48, same for player, so the distance between their middle points is 48
    ///the zombie should stop right before he hits the player (48 + 1 pixel padding) so he won't push the player
    if(direction.length() > 49) {
        direction.normalize();
        direction *= 1.5f;
        this->updatePositionInComp(direction);
    }
    if(direction.getY() < 0 && std::abs(direction.getY()) > std::abs(direction.getX())) m_direction = "up";
    if(direction.getY() > 0 && std::abs(direction.getY()) > std::abs(direction.getX())) m_direction = "down";
    if(direction.getX() < 0 && std::abs(direction.getX()) > std::abs(direction.getY())) m_direction = "left";
    if(direction.getX() > 0 && std::abs(direction.getX()) > std::abs(direction.getY())) m_direction = "right";
}

Zombie& Zombie::operator=(const Zombie &rhs) {
    if(&rhs == this) {
        return *this;
    }
    Entity::operator=(rhs);
    lastHit = rhs.lastHit;
    m_generator = rhs.m_generator;
    std::ifstream in("Init/world.txt");
    for(int i = 0; i < MAP_HEIGHT; i++) {
        for(int j = 0; j < MAP_WIDTH; j++) {
            in >> obstacleReader;
            if(obstacleReader != 0) {
                m_generator.addCollision({i, j});
            }
        }
    }
    in.close();
    return *this;
}
