#pragma once

#include <AStar.h>
#include <vector>
#include <string>
#include <SFML/System/Vector2.hpp>

#include "../header/Singleton.h"

class ObstacleManager : public Singleton<ObstacleManager>{
    std::vector<sf::Vector2i> obstacles;
protected:
    ObstacleManager() = default;
public:
    void loadObstaclesWithBuffer(const std::string& filePath, int mapHeight, int mapWidth);
    const std::vector<sf::Vector2i>& getObstacles() const;
};