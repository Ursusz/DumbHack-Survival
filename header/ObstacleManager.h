#pragma once

#include <AStar.h>
#include <vector>
#include <string>
#include <SFML/System/Vector2.hpp>

class ObstacleManager {
public:
    static ObstacleManager& getInstance();

    void loadObstaclesWithBuffer(const std::string& filePath, int mapHeight, int mapWidth);
    const std::vector<sf::Vector2i>& getObstacles() const;

private:
    ObstacleManager() = default;
    std::vector<sf::Vector2i> obstacles;
};